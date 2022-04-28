/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 16:14:25 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/28 12:56:08 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	rand_double(void)
{
	double	random;

	random = rand() / (RAND_MAX + 1.0);
	return (random);
}

double	rand_double_min_max(double min, double max)
{
	return (min + (max - min) * rand_double());
}

t_vec3	vec3_random(void)
{
	return (vec3_init(rand_double(), rand_double(), rand_double()));
}

t_vec3	vec3_random_min_max(double min, double max)
{
	return (vec3_init(rand_double_min_max(min, max),
			rand_double_min_max(min, max),
			rand_double_min_max(min, max)));
}

t_vec3	random_in_unit_sphere(void)
{
	t_vec3	p;

	while (true)
	{
		p = vec3_random_min_max(-1, 1);
		if (length_sqrd(p) < 1)
			return (p);
	}
}
