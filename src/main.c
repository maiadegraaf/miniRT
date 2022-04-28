/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:16:40 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/04/28 12:53:57 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_img(t_mlx_win	*win, t_cam *cam, t_hittable_lst *world)
{
	double	u;
	double	v;
	t_ray	ray;
	t_vec3	color;
	int		samples_per_pixel;
	double	s;
	double	t;

	samples_per_pixel = 100;
	win->y = win->height - 1;
	while (win->y >= 0)
	{
		win->x = 0;
		while (win->x < win->width)
		{
			color = vec3_init(0, 0, 0);
			s = 0.1;
			while (s < 1)
			{
				u = (win->x + s) / (win->width - 1);
				t = 0.1;
				while (t < 1)
				{
					v = (win->y + t) / (win->height - 1);
					ray = get_ray(*cam, u, v);
					color = vec3_add(ray_color(&ray, world, 10), color);
					t += 0.1;
				}
				s += 0.1;
			}
			write_color(&color, win, 100);
			win->x++;
		}
		win->y--;
	}
}

t_cam	setup_cam(t_mlx_win *win)
{
	t_cam	cam;

	(void) win;
	cam.vp_h = 2.0;
	cam.vp_w = ASPECT_RATIO * cam.vp_h;
	cam.foc_l = 1.0;
	cam.origin = vec3_init(0, 0, 0);
	cam.hor = vec3_init(cam.vp_w, 0, 0);
	cam.vert = vec3_init(0, cam.vp_h, 0);
	cam.btm_l_corner = vec3_sub(vec3_sub(vec3_sub(
					cam.origin,
					(vec3_div(2, cam.hor))),
				(vec3_div(2, cam.vert))),
			vec3_init(0, 0, cam.foc_l));
	return (cam);
}

void	create_obj(t_hittable_lst **world, t_sphere sphere)
{
	t_hittable_lst	*node;

	node = hittable_lst_new(sphere, SPHERE);
	if (!node)
		perror("malloc ");
	hittable_lst_add_back(world, node);
}

int32_t	main(void)
{
	mlx_t			*mlx;
	t_mlx_win		win;
	t_cam			cam;
	t_hittable_lst	*world;

	win.width = 800;
	win.height = (int)(win.width / ASPECT_RATIO);
	mlx = mlx_init(win.width, win.height, "miniRT", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	cam = setup_cam(&win);
	g_img = mlx_new_image(mlx, win.width, win.height);
	world = NULL;
	create_obj(&world, sphere_init(vec3_init(0, 0, -1), 0.5));
	create_obj(&world, sphere_init(vec3_init(0, -10.5, -1), 10));
	color_img(&win, &cam, world);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
