/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:20:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/13 17:52:44 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

bool	find_object_in_front(t_hittable light_hit, t_ray r, t_hittable_lst *world)
{
	t_hittable		hit;
	float	tmp_t;
	t_hittable_lst	*start;
	bool			ret;

	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	start = world;
	hit_hittable_list(light_hit, world);
	tmp_t = light_hit.rec->t;
	ret = false;
	world = ft_hittable_lstlast(world);
	while (start)
	{
		if (hit_hittable_list(hit, start))
		{
			if (hit.rec->t < tmp_t)
				ret = true;
		}
		start = start->prev;
	}
	return (ret);
}

t_point_light point_light_init(t_vec4 position, t_vec4 color, float power)
{
	t_point_light	node;

	node.position = position;
	node.diff_color = color;
	node.diff_power = power;
	node.spec_color = (t_vec4){1, 1, 1, 1};
	node.spec_power = 2;
	return (node);
}

void	check_shadow(t_hittable_lst *world, t_ray light_r, t_lighting *l)
{
	t_hittable light_hit;

	light_hit = hittable_init(&light_r, 0, INFINITY, hit_rec_init_empty());
	if (find_object_in_front(light_hit, light_r, world))
		l->if_s = true;
}

t_lighting get_point_light(t_point_light light, t_hittable hittable, t_hittable_lst *world)
{
	t_lighting	l;
	t_vec4		light_dir;
	float		distance;
	float		intensity;
	t_vec4		h;

	l.diff = BLACK;
	l.spec = BLACK;
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
		check_shadow(world, ray_init(light.position, -light_dir), &l);
	}
	return (l);
}