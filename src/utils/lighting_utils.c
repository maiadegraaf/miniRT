/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:20:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/09 13:37:23 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	check_shadow(t_hittable_lst *world, t_ray light_r, t_lighting *l, t_vec4 l_color, float distance)
{
	t_hittable light_hit;

	light_hit = hittable_init(&light_r, 0, INFINITY, hit_rec_init_empty());
	while (world->prev != NULL)
	{
		world = world->prev;
		if (hit_hittable_list(light_hit, world))
		{
			l->if_s = true;
			// float	intensity = -((distance - light_hit.rec->t)/200 - hit_sphere(world->s, *light_hit.r)) / 50;
			float intensity = clamp(dot(light_hit.rec->n, -light_hit.r->dir), 0, 1);
			// printf("intenstiy = %f\n", intensity);
			// (void) distance;
			l->shadow = world->next->color / (1 - intensity * l_color / distance);
			l->shadow[0] = clamp(l->shadow[0], 0, l->diff[0] + l->spec[0]);
			l->shadow[1] = clamp(l->shadow[1], 0, l->diff[1] + l->spec[1]);
			l->shadow[2] = clamp(l->shadow[2], 0, l->diff[2] + l->spec[2]);
			return ;
		}
	}
}

t_lighting get_point_light(t_point_light light, t_hittable hittable, t_hittable_lst *world)
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
		l.diff = world->color * intensity * light.diff_color * light.diff_power / distance;
		h = unit_vector(-light_dir + hittable.r->dir);
		intensity = pow((float)dot(hittable.rec->n, h), 120);
		l.spec = intensity * light.spec_color / distance;
		check_shadow(world, ray_init(light.position, -light_dir), &l, light.diff_color, distance);
	}
	return (l);
}