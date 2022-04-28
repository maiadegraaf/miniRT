/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec3.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 14:29:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/22 14:27:07 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H
# include "minirt.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

//utils
double	length_sqrd(t_vec3 v);
double	length(t_vec3 v);
t_vec3	unit_vector(t_vec3 v);
t_vec3	vec3_init(double x, double y, double z);

//operations
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult(t_vec3 a, t_vec3 b);
t_vec3	vec3_mult_d(double t, t_vec3 a);
t_vec3	vec3_div(double t, t_vec3 a);

#endif