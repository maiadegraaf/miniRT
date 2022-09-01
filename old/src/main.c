/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 11:16:40 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/05/03 18:06:16 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_img(t_mlx_win	*win, t_cam *cam, t_hittable_lst *world)
{
	float	u;
	float	v;
	t_ray	ray;
	t_vec4	color;
	float	s;
	float	t;

	win->y = win->height - 1;
	while (win->y >= 0)
	{
		win->x = 0;
		while (win->x < win->width)
		{
			color = (t_vec4){0};
			s = 0.1;
			while (s < 1)
			{
				u = (win->x + s) / (win->width - 1);
				t = 0.1;
				while (t < 1)
				{
					v = (win->y + t) / (win->height - 1);
					ray = get_ray(*cam, u, v);
					color += ray_color(&ray, world, 10);
					t += 0.1;
				}
				s += 0.1;
			}
			write_color(color, win, 100);
			win->x++;
		}
		win->y--;
	}
}

t_cam	setup_cam(t_vec4 look_frm, t_vec4 look_at, t_vec4 vup, float vfov)
{
	t_cam	cam;
	float	theta;
	float	h;
	t_vec4	w;
	t_vec4	u;
	t_vec4	v;

	theta = deg_to_rad(vfov);
	h = tan(theta / 2);
	// cam.vp_h = (float)2.0 * h;
	cam.vp_h = (float)2;
	cam.vp_w = ASPECT_RATIO * cam.vp_h;
	w = unit_vector(look_frm - look_at);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	cam.foc_l = (float)1;
	cam.origin = (t_vec4){0};
	cam.hor = (t_vec4){cam.vp_w, 0, 0, 0};
	cam.vert = (t_vec4){0, cam.vp_h, 0, 0};
	cam.btm_l_corner = cam.origin - (cam.hor / 2) - (cam.vert / 2)
		- (t_vec4){0, 0, cam.foc_l, 0};
	// cam.foc_l = 1.0;
	// cam.origin = look_frm;
	// cam.hor = cam.vp_w * u;
	// cam.vert = cam.vp_h * v;
	// cam.btm_l_corner = cam.origin - (cam.hor / 2) - (cam.vert / 2) - w;
	return (cam);
}

void	create_obj(t_hittable_lst **world, t_sphere sphere, t_vec4 color)
{
	t_hittable_lst	*node;

	node = hittable_lst_new(sphere, SPHERE, color);
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
	cam = setup_cam((t_vec4){-2, 2, 1, 0}, (t_vec4){0, 0, -1, 0},
			(t_vec4){0, 1, 0, 0}, 90);
	g_img = mlx_new_image(mlx, win.width, win.height);
	world = NULL;
	create_obj(&world, sphere_init((t_vec4){0, 0, -1, 0}, 0.5),
		(t_vec4){1, 0.4, 0, 0});
	// create_obj(&world, sphere_init((t_vec4){-1, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.8, 0.5, 1, 0});
	// create_obj(&world, sphere_init((t_vec4){1, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.55, 0.55, 0.55, 0});
	// create_obj(&world, sphere_init((t_vec4){0, -100.5, -1, 0}, 100),
	// 	(t_vec4){0.8, 1, 0.2, 0});
	color_img(&win, &cam, world);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
