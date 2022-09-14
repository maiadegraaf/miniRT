/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 16:05:55 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 16:06:07 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_lighting	get_point_light(t_point_light light,
	t_hittable hittable, t_hittable_lst *world)
{
	t_lighting	l;
	t_vec4		light_dir;
	float		distance;
	float		intensity;
	t_vec4		h;

	l.diff = (t_vec4){0, 0, 0, 0};
	l.spec = (t_vec4){0, 0, 0, 0};
	l.if_s = false;
	if (light.diff_power > 0)
	{
		light_dir = light.position - hittable.rec->p;
		distance = length(light_dir);
		light_dir = unit_vector(light_dir);
		distance *= distance;
		intensity = clamp(dot(hittable.rec->n, light_dir), 0, 1);
		l.diff = world->color * intensity * light.diff_color
			* light.diff_power / distance;
		h = unit_vector(-light_dir + hittable.r->dir);
		intensity = pow((float)dot(hittable.rec->n, h), 120);
		l.spec = intensity * light.spec_color / distance;
		check_shadow(world, ray_init(light.position, -light_dir), &l);
	}
	return (l);
}
