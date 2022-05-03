/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 14:04:24 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/05/03 15:51:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	length_sqrd(t_vec4 v)
{
	return ((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

float	length(t_vec4 v)
{
	return (sqrt(length_sqrd(v)));
}

t_vec4	unit_vector(t_vec4 v)
{
	return (v / length(v));
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3_init(-v.x, -v.y, -v.z));
}

t_vec3	vec3_init(float x, float y, float z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
