/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   math_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:59:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/19 16:24:17 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	rodrigues(t_vec4 v, t_vec4 axis, float angle)
{
	if (angle == 0 || angle == M_PI)
		return (v);
	return (v * cosf(angle)
		+ cross(axis, v) * sinf(angle)
		+ axis * dot(axis, v) * (1 - cosf(angle)));
}

float	quadratic(t_abc abc)
{
	float	delta;
	float	t;
	float	t2;

	delta = pow(abc.b, 2) - 4 * abc.a * abc.c;
	if (delta < 0)
		return (-1);
	t = (-abc.b - sqrt(delta)) / (2 * abc.a);
	t2 = (-abc.b + sqrt(delta)) / (2 * abc.a);
	if ((t2 < t && t2 >= 0) || t < 0)
		t = t2;
	return (t);
}

float	angle(t_vec4 v, t_vec4 u)
{
	return (acos(dot(v, u) / (length(v) * length(u))));
}

t_vec4	project(t_vec4 v, t_vec4 u)
{
	return (u * (dot(u, v) / dot(v, u)));
}
