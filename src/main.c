/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/15 18:26:44 by mgraaf        ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_win			win;
	t_elements		elements;

	if (argc < 2)
		ft_error(20);
	elements = parse_input(argv[1]);
	win = setup_win(&mlx);
	paint_img(win, elements);
	mlx_image_to_window(mlx, win.img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
