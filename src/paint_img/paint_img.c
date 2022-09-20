/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paint_img.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:16:41 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/20 14:31:00 by mgraaf        ########   odam.nl         */
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
			color = ray_color(get_ray(*elements.cam, i, j, win), &elements);
			// ANTIALIASING:
			// color = antialiasing(i, j, elements, win);
			write_color(color, i, j, win);
			i++;
		}
		j++;
	}
}

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
