/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:17:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/06 14:57:40 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "minirt.h"

typedef struct s_hittable t_hittable;

typedef struct s_lighting
{
	t_vec4	diff;
	t_vec4	spec;
} t_lighting;

typedef struct s_point_light
{
	t_vec4	position;
	t_vec4	diff_color;
	float	diff_power;
	t_vec4	spec_color;
	float	spec_power;
} t_point_light;

t_point_light point_light_init(t_vec4	position, t_vec4 color, float power);
t_lighting get_point_light(t_point_light light, t_hittable hittable);

#endif // LIGHTING_H