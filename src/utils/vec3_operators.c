/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3_operators.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 14:35:18 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/21 17:40:20 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_init((a.x + b.x), (a.y + b.y), (a.z + b.z)));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3_init((a.x - b.x), (a.y - b.y), (a.z - b.z)));
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return (vec3_init((a.x * b.x), (a.y * b.y), (a.z * b.z)));
}

t_vec3	vec3_mult_d(double t, t_vec3 a)
{
	return (vec3_init((a.x * t), (a.y * t), (a.z * t)));
}

t_vec3	vec3_div(double t, t_vec3 a)
{
	return (vec3_mult_d((1 / t), a));
}
