/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 16:14:25 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/05/03 15:36:17 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	rand_float(void)
{
	float	random;

	random = rand() / (RAND_MAX + 1.0);
	return (random);
}

float	rand_float_min_max(float min, float max)
{
	return (min + (max - min) * rand_float());
}

t_vec4	vec3_random(void)
{
	return (vec3_init(rand_float(), rand_float(), rand_float()));
}

t_vec4	vec3_random_min_max(float min, float max)
{
	return (vec3_init(rand_float_min_max(min, max),
			rand_float_min_max(min, max),
			rand_float_min_max(min, max)));
}

t_vec4	random_in_unit_sphere(void)
{
	t_vec4	p;

	while (true)
	{
		p = vec3_random_min_max(-1, 1);
		if (length_sqrd(p) < 1)
			return (p);
	}
}
