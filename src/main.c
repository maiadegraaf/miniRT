/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:08:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/22 14:26:20 by mgraaf        ########   odam.nl         */
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

void	_mlx_keypress(keys_t key)
{
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}

void	free_elements(t_elements *elements)
{
	if (elements->ambient)
		free(elements->ambient);
	free(elements->cam);
	if (elements->light)
		free(elements->light);
	ft_hittable_lstclear(&elements->objs);
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
	mlx_key_hook(mlx, (mlx_keyfunc)_mlx_keypress, mlx);
	free_elements(&elements);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
