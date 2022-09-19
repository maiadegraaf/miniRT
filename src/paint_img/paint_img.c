/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paint_img.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:16:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/15 18:23:10 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	paint_img(t_win	win, t_elements elements)
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
			// color = ray_color(get_ray(*elements.cam, i, j, win), &elements);
			// ANTIALIASING:
			color = send_antialiasing(i, j, elements, win);
			write_color(color, i, j, win);
			i++;
		}
		j++;
	}
}

// void	*paint_img(void *tmp)
// {
// 	int			j;
// 	int			i;
// 	t_vec4		color;
// 	t_painter	*painter;

// 	painter = tmp;
// 	j = painter->y_min;
// 	while (j < painter->h && j <= painter->y_max)
// 	{
// 		i = painter->x_min;
// 		while (i < painter->w && i <= painter->x_max)
// 		{
// 			// printf("{%d, %d}\n", i, j);
// 			// NON ANTIALIASING:
// 			color = ray_color(get_ray(*painter->elements.cam,
// 						i, j, *painter), &painter->elements);
// 			// ANTIALIASING:
// 			// color = antialiasing(i, j, elements, win);
// 			// printf("i = %d, j = %d\n", i, j);
// 			write_color(color, i, j, &painter->win);
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (NULL);
// }

int	join_threads(pthread_t painters[THREADS])
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(painters[i], NULL) != 0)
			return (1);
		i++;
	}
	return (1);
}

// t_painter	set_painter(t_range x, t_range y, t_elements elements, t_win win)
// {
// 	t_painter	painter;

// 	painter.elements = elements;
// 	painter.win = &win;
// 	painter.h = win.h;
// 	painter.w = win.w;
// 	painter.x_min = x.min;
// 	painter.x_max = x.min + x.max;
// 	if (painter.x_max + x.max >= win.w)
// 		painter.x_max = win.w;
// 	painter.y_min = y.min;
// 	painter.y_max = y.min + y.max;
// 	if (painter.y_max + y.max >= win.h)
// 		painter.y_max = win.h;
// 	return (painter);
// }

// void	create_painters(t_win win, t_elements elements)
// {
// 	t_painter	painter;
// 	int			x_increase;
// 	int			y_increase;
// 	int			i;
// 	pthread_t	painters[THREADS];
// 	float		w_inc;
// 	float		h_inc;

// 	i = 0;
// 	y_increase = 0;
// 	w_inc = win.w / 10;
// 	h_inc = 100;
// 	while (y_increase < win.h)
// 	{
// 		x_increase = 0;
// 		while (x_increase < win.w)
// 		{
// 			painter = set_painter(range_init(x_increase, w_inc),
// 					range_init(y_increase, h_inc), elements, win);
// 			// printf("-----%d-----\nx range = {%d, %d}\ny range = {%d, %d}\n\n", i, painter.x_min, painter.x_max, painter.y_min, painter.y_max);
// 			if (pthread_create(&painters[i++], NULL, &paint_img, &painter))
// 				ft_error(10);
// 			x_increase += w_inc;
// 		}
// 		y_increase += h_inc;
// 	}
// 	join_threads(painters);
// }
