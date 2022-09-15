/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialiasing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:16:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/15 18:25:58 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	send_antialiasing(int i, int j, t_elements elements, t_win win)
{
	t_thread_data	data;
	pthread_t		thread;

	data.i = i;
	data.j = j;
	data.elements = elements;
	data.win = win;
	data.color = (t_vec4){0, 0, 0, 0};
	if (pthread_create(&thread, NULL, &antialiasing, &data))
		ft_error(10);
	return (data.color);
}

void	*antialiasing(void *tmp)
{
	float			s;
	float			t;
	t_thread_data	*data;

	data = tmp;
	s = 0.1;
	while (s < 1)
	{
		t = 0.1;
		while (t < 1)
		{
			data->color = data->color + ray_color(
					get_ray(*data->elements.cam, data->i + s,
						data->j + t, data->win), &data->elements);
			t += 0.1;
		}
		s += 0.1;
	}
	data->color *= (float)0.01;
	pthread_exit(NULL);
	return (NULL);
}

// t_vec4	antialiasing(int i, int j, t_elements elements, t_win win)
// {
// 	float	s;
// 	float	t;
// 	t_vec4	color;

// 	s = 0.1;
// 	while (s < 1)
// 	{
// 		t = 0.1;
// 		while (t < 1)
// 		{
// 			color = color + ray_color(
// 					get_ray(*elements.cam, i + s, j + t, win), &elements);
// 			t += 0.1;
// 		}
// 		s += 0.1;
// 	}
// 	color *= (float)0.01;
// 	return (color);
// }