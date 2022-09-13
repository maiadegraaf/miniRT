/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/13 17:20:19 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam setup_cam(t_vec4 look_from, t_vec4 look_at, t_vec4 vup, float vfov)
{
	t_cam	n;
	t_vec4	w;
	t_vec4	u;
	t_vec4	v;

	n.vfov = vfov;
	n.theta = deg_to_rad(n.vfov);
	n.h = tan((float)n.theta/2);
	n.vp_h = (float)(2.0 * n.h);
	n.vp_w = ASPECT_RATIO * n.vp_h;
	n.focal_len = 1.0;
	w = unit_vector(look_from - look_at);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	n.orig = look_from;
	n.horiz = n.vp_w * u;
	n.vert = n.vp_h * v;
	n.btm_left_cnr = n.orig - n.horiz/2 - n.vert/2 - w;
	return (n);
}

void	create_obj(t_hittable_lst **world, t_sphere *sphere, t_vec4 color)
{
	t_hittable_lst	*node;

	node = ft_hittable_lstnew(sphere, color);
	if (!node)
		perror("malloc ");
	ft_hittable_lstadd_back(world, node);
}

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_win			win;
	// t_cam			cam;
	// t_hittable_lst	*world;
	t_elements		elements;

	win.w = WIDTH;
	win.h = (int)(win.w / ASPECT_RATIO);
	mlx = mlx_init(win.w, win.h, "miniRT", true);
	g_img = mlx_new_image(mlx, win.w, win.h);

	if (argc < 2)
		ft_error(20);
	
	elements = parse_input(argv[1]);
	// world = NULL;
	// float	r = cos((float)(M_PI/4));

	// create_obj(&world, sphere_init((t_vec4){-1, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.5, 0.2, 0.1});
	// create_obj(&world, sphere_init((t_vec4){0, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.1, 0.2, 0.5});
	// create_obj(&world, sphere_init((t_vec4){1, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.8, 0.6, 0.2});
	// create_obj(&world, sphere_init((t_vec4){0, -100.5, -1, 0}, 100),
	// 	(t_vec4){0.8, 0.8, 0.8});

	// create_obj(&world, sphere_init((t_vec4){r, 0, -1, 0}, r),
	// 	(t_vec4){1, 0, 0, 0});
	// create_obj(&world, sphere_init((t_vec4){-r, 0, -1, 0}, r),
	// 	(t_vec4){0, 0, 1, 0});

	// create_obj(&world, sphere_init((t_vec4){0, 0, -1, 0}, 0.5),
	// 	(t_vec4){0.8, 0.4, 0.8, 0});
	// create_obj(&world, sphere_init((t_vec4){0, -100.5, -1, 0}, 100),
	// 	(t_vec4){0.3, 0.1, 0.8, 0});
	// printf("{%f, %f, %f}\n", world->s->center[0], world->s->center[1], world->s->center[2]);
	// printf("{%f, %f, %f}\n", world->s->center[0], world->s->center[1], world->s->center[2]);

	// *elements.cam = setup_cam((t_vec4){-3, 1, 1}, (t_vec4){0, 0, -1}, (t_vec4){0, 1, 0}, 90);
	int j = 0;
	while (j < win.h)
	{
		int i = 0;
		while (i < win.w)
		{
			float u = ((float) i) / (win.w - 1);
			float v = ((float) j) / (win.h - 1);
			t_ray r = get_ray(*elements.cam, u, v);
			t_vec4 color = ray_color(r, &elements);

			// float s = 0.1;
			// while (s < 1)
			// {
			// 	float u = ((float) i + s) / (win.w - 1);
			// 	float t = 0.1;
			// 	while (t < 1)
			// 	{
			// 		float v = ((float) j + t) / (win.h - 1);
			// 		t_ray r = get_ray(cam, u, v);
			// 		color = color + ray_color(r, world);
			// 		t += 0.1;
			// 	}
			// 	s += 0.1;
			// }
			// printf("[%d, %d]\n", i, j);
			write_color(color, i, j, win);
			i++;
		}
		j++;
	}
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
