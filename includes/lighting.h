/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:17:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/13 13:10:52 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "minirt.h"

typedef struct s_hittable t_hittable;
typedef struct s_hittable_lst t_hittable_lst;

typedef struct s_ambient
{
	float	strength;
	t_vec4	color;
}	t_ambient;

typedef struct s_lighting
{
	t_vec4	diff;
	t_vec4	spec;
	bool	if_s;
	t_vec4	shadow;
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
t_lighting get_point_light(t_point_light light, t_hittable hittable, t_hittable_lst *world);

#endif // LIGHTING_H