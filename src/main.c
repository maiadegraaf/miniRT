/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/06 13:49:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cam setup_cam(void)
{
	t_cam n;
	n.vp_h = 2.0;
	n.vp_w = ASPECT_RATIO * n.vp_h;
	n.focal_len = 1.0;
	n.orig = (t_vec4){0, 0, 0, 0};
	n.horiz = (t_vec4){n.vp_w, 0, 0, 0};
	n.vert = (t_vec4){0, n.vp_h, 0, 0};
	n.btm_left_cnr = n.orig - n.horiz/2 - n.vert/2 - (t_vec4){0, 0, n.focal_len, 0};
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

int	main(void)
{
	mlx_t			*mlx;
	t_win			win;
	t_cam			cam;
	t_hittable_lst	*world;

	win.w = WIDTH;
	win.h = (int)(win.w / ASPECT_RATIO);
	mlx = mlx_init(win.w, win.h, "miniRT", true);
	g_img = mlx_new_image(mlx, win.w, win.h);

	world = NULL;
	create_obj(&world, sphere_init((t_vec4){0, 0, -1, 0}, 0.5),
		(t_vec4){1, 0.4, 0, 0});
	// printf("{%f, %f, %f}\n", world->s->center[0], world->s->center[1], world->s->center[2]);
	create_obj(&world, sphere_init((t_vec4){0, -100.5, -1, 0}, 100),
		(t_vec4){1, 1, 1, 0});
	// printf("{%f, %f, %f}\n", world->s->center[0], world->s->center[1], world->s->center[2]);

	cam = setup_cam();
	int j = 0;
	while (j < win.h)
	{
		int i = 0;
		while (i < win.w)
		{
			t_vec4 color = (t_vec4){0, 0, 0, 0};
			float s = 0.1;
			while (s < 1)
			{
				float u = ((float) i + s) / (win.w - 1);
				float t = 0.1;
				while (t < 1)
				{
					float v = ((float) j + t) / (win.h - 1);
					t_ray r = get_ray(cam, u, v);
					color = color + ray_color(r, world);
					t += 0.1;
				}
				s += 0.1;
			}
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
