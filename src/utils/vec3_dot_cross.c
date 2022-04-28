/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_dot_cross.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 11:32:53 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/22 11:37:44 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot(t_vec3 u, t_vec3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vec3	cross(t_vec3 u, t_vec3 v)
{
	return (vec3_init((u.y * v.z) - (u.z * u.y),
			(u.z * v.x) - (u.x * u.z),
			(u.x * v.y) - (u.y * u.x)));
}
