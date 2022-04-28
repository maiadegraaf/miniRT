/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 14:04:24 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/22 15:15:04 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	length_sqrd(t_vec3 v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	length(t_vec3 v)
{
	return (sqrt(length_sqrd(v)));
}

t_vec3	unit_vector(t_vec3 v)
{
	return (vec3_div(length(v), v));
}

t_vec3	vec3_neg(t_vec3 v)
{
	return (vec3_init(-v.x, -v.y, -v.z));
}

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
