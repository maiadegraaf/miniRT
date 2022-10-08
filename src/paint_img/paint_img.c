/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paint_img.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:16:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/10/08 16:21:59 by maiadegraaf   ########   odam.nl         */
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
			if (ANTI == 1)
				color = antialiasing(i, j, elements, win);
			else
				color = ray_color(get_ray(*elements.cam, i, j, win), &elements);
			write_color(color, i, j, win);
			i++;
		}
		j++;
	}
}
