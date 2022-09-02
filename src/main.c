/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/02 10:09:15 by maiadegraaf   ########   odam.nl         */
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

int	main(void)
{
	mlx_t	*mlx;
	t_win	win;
	t_cam	cam;

	win.w = WIDTH;
	win.h = (int)(win.w / ASPECT_RATIO);
	mlx = mlx_init(win.w, win.h, "miniRT", true);
	g_img = mlx_new_image(mlx, win.w, win.h);
	cam = setup_cam();
	int j = 0;
	while (j < win.h)
	{
		int i = 0;
		while (i < win.w)
		{
			float u = ((float) i) / (win.w - 1);
			float v = ((float) j) / (win.h - 1);
			t_ray r = ray_init(cam.orig, cam.btm_left_cnr + u * cam.horiz + v * cam.vert - cam.orig);
			t_vec4 color = ray_color(r);
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
