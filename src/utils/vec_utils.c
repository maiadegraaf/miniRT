/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:48:17 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/08/31 17:11:22 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	length_squared(t_vec4 v)
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float	length(t_vec4 v)
{
	return (sqrt(length_squared(v)));
}

float	dot(const t_vec4 u, const t_vec4 v)
{
	return (u[0] * v[0]
		+ u[1] * v[1]
		+ u[2] * v[2]);
}

t_vec4	cross(const t_vec4 u, const t_vec4 v)
{
	t_vec4	n;

	n[0] = u[1] * v[2] - u[2] * v[1];
	n[1] = u[2] * v[0] - u[0] * v[2];
	n[2] = u[0] * v[1] - u[1] * v[0];
	n[3] = 0;
	return (n);
}

t_vec4	unit_vector(t_vec4 v)
{
	return (v / length(v));
}
