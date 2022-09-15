/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:49:06 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/15 15:10:24 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int	closest_obj(t_ray r, t_hittable_lst *world, bool *ret)
{
	int				i;
	int				j;
	t_hittable		hit;
	float			tmp_t;

	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	i = 0;
	j = 0;
	tmp_t = INFINITY;
	while (world)
	{
		if (hit_hittable_list(hit, world))
		{
			if (hit.rec->t < tmp_t)
			{
				tmp_t = hit.rec->t;
				i = j;
			}
			*ret = true;
		}
		j++;
		world = world->next;
	}
	return (i);
}

t_hittable_lst	*find_world_touched_first(t_ray r, t_hittable_lst *world)
{
	int				i;
	int				j;
	bool			ret;

	ret = false;
	i = closest_obj(r, world, &ret);
	j = 0;
	while (i != 0 && world && j < i)
	{
		world = world->next;
		j++;
	}
	if (ret == true)
		return (world);
	return (NULL);
}

t_vec4	ray_color(t_ray r, t_elements *elements)
{
	t_hittable		hit;
	t_lighting		lighting;
	t_hittable_lst	*world;

	world = elements->objs;
	world = find_world_touched_first(r, world);
	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	if (world && hit_hittable_list(hit, world))
	{
		lighting = get_point_light(*elements->light, hit, world);
		if (lighting.if_s == true)
			return ((world->color * elements->ambient->color));
		return ((world->color * elements->ambient->color)
			+ lighting.diff + lighting.spec);
	}
	return ((t_vec4){0, 0, 0, 0});
}
