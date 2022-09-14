/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 14:25:11 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_win	setup_win(mlx_t **mlx)
{
	t_win	win;

	win.w = WIDTH;
	win.h = (int)(win.w / ASPECT_RATIO);
	*mlx = mlx_init(win.w, win.h, "miniRT", true);
	win.img = mlx_new_image(*mlx, win.w, win.h);
	return (win);
}

t_vec4	antialiasing(int i, int j, t_elements elements, t_win win)
{
	float	s;
	float	t;
	t_vec4	color;

	s = 0.1;
	while (s < 1)
	{
		t = 0.1;
		while (t < 1)
		{
			color = color + ray_color(
					get_ray(*elements.cam, i + s, j + t, win), &elements);
			t += 0.1;
		}
		s += 0.1;
	}
	color *= (float)0.01;
	return (color);
}

void	print_img(t_win	win, t_elements elements)
{
	int		j;
	int		i;
	t_vec4	color;

	j = 0;
	while (j < win.h)
	{
		i = 0;
		while (i < win.w)
		{
			// NON ANTIALIASING:
			color = ray_color(get_ray(*elements.cam, i, j, win), &elements);
			// ANTIALIASING:
			// color = antialiasing(i, j, elements, win);
			write_color(color, i, j, win);
			i++;
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_win			win;
	t_elements		elements;

	if (argc < 2)
		ft_error(20);
	elements = parse_input(argv[1]);
	win = setup_win(&mlx);
	print_img(win, elements);
	mlx_image_to_window(mlx, win.img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
