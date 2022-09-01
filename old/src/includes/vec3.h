/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 14:29:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/05/03 15:36:17 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include "minirt.h"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec4;

//utils
float	length_sqrd(t_vec4 v);
float	length(t_vec4 v);
t_vec4	unit_vector(t_vec4 v);
t_vec4	vec3_init(float x, float y, float z);

//operations
t_vec4	vec3_add(t_vec4 a, t_vec4 b);
t_vec4	vec3_sub(t_vec4 a, t_vec4 b);
t_vec4	vec3_mult(t_vec4 a, t_vec4 b);
t_vec4	vec3_mult_d(float t, t_vec4 a);
t_vec4	vec3_div(float t, t_vec4 a);

#endif