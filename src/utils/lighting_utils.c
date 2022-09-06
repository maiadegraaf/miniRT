/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:20:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/06 18:06:03 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_point_light point_light_init(t_vec4	position, t_vec4 color, float power)
{
	t_point_light	node;

	node.position = position;
	node.diff_color = color;
	node.diff_power = power;
	node.spec_color = (t_vec4){1, 1, 1, 1};
	node.spec_power = 10;
	return (node);
}

t_lighting get_point_light(t_point_light light, t_hittable hittable)
{
	t_lighting	l;
	t_vec4		light_dir;
	float		distance;
	float		intensity;
	t_vec4		h;

	l.diff = (t_vec4){0, 0, 0, 0};
	l.spec = (t_vec4){0, 0, 0, 0};
	if (light.diff_power > 0)
	{
		light_dir = light.position - hittable.rec->p;
		distance = length(light_dir);
		light_dir = unit_vector(light_dir);
		distance *= distance;
		intensity = clamp(dot(hittable.rec->n, light_dir), 0, 1);
		l.diff = intensity * light.diff_color * light.diff_power / distance;

		h = unit_vector(light_dir + hittable.r->dir);
		intensity = pow(clamp(dot(hittable.rec->n, h), 0, 1), 2.5);
		if (intensity > (float)0.00001)
			printf("intensity = %f\n", intensity);
		l.spec = intensity * light.spec_color * light.spec_power / distance;
		// if (l.spec[0] > 0.01)
		// 	printf("%f, %f, %f\n", l.spec[0], l.spec[1], l.spec[2]);
	}
	return (l);
}