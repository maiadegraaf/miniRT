/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialiasing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 14:16:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/19 13:07:31 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
