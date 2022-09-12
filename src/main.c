/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/12 14:45:40 by mgraaf        ########   odam.nl         */
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

t_win	setup_win(mlx_t **mlx)
{
	t_win	win;

	win.w = WIDTH;
	win.h = (int)(win.w / ASPECT_RATIO);
	*mlx = mlx_init(win.w, win.h, "miniRT", true);
	win.img = mlx_new_image(*mlx, win.w, win.h);
	win.x = 0;
	win.y = 0;
	return (win);
}

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_elements		elements;
	t_win			win;
	t_cam			cam;

	if (argc != 2)
		ft_error(20);
	elements = parse_input(argv[1]);

	cam = setup_cam((t_vec4){-2, 2, 1}, (t_vec4){0, 0, -1}, (t_vec4){0, 1, 0}, 100);
	while (win.y < win.h)
	{
		win.x = 0;
		while (win.x < win.w)
		{
			float u = ((float) win.x) / (win.w - 1);
			float v = ((float) win.y) / (win.h - 1);
			t_ray r = get_ray(cam, u, v);
			t_vec4 color = ray_color(r, world);

			// float s = 0.1;
			// while (s < 1)
			// {
			// 	float u = ((float) win.x + s) / (win.w - 1);
			// 	float t = 0.1;
			// 	while (t < 1)
			// 	{
			// 		float v = ((float) win.y + t) / (win.h - 1);
			// 		t_ray r = get_ray(cam, u, v);
			// 		color = color + ray_color(r, world);
			// 		t += 0.1;
			// 	}
			// 	s += 0.1;
			// }
			// printf("[%d, %d]\n", win.x, win.y);
			write_color(color, win);
			win.x++;
		}
		win.y++;
	}
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
