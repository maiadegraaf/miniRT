/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:34:40 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/08 16:40:50 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_hittable_lst	*find_world_touched_first(t_ray r, t_hittable_lst *world)
{
	t_hittable		hit;
	t_hit_record	*tmp_hit;
	int	i;
	t_hittable_lst	*start;
	int 			j;
	bool			ret;

	i = 0;
	j = 0;
	start = world;
	tmp_hit = hit_rec_init_empty();
	tmp_hit->t = INFINITY;
	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	ret = false;
	while (start)
	{
		if (hit_hittable_list(hit, start))
		{
			if (hit.rec->t < tmp_hit->t)
			{
				tmp_hit->t = hit.rec->t;
				i = j;
			}
			ret = true;
		}
		j++;
		start = start->next;
	}
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

t_vec4 ray_color(t_ray r, t_hittable_lst *world)
{
	t_vec4			unit_dir;
	float			t;
	t_hittable		hit;
	t_lighting		lighting;

	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	world = find_world_touched_first(r, world);
	if (world)
	{
		lighting = get_point_light(point_light_init((t_vec4){3, 0, -0.5, 0},
				world->color, 5), hit, world);
		if (lighting.if_s == true)
			return (lighting.shadow);
		return (world->color + lighting.diff + lighting.spec);
	}
	unit_dir = unit_vector(r.dir);
	t = (float)0.5 * (unit_dir[1] + (float)1.0);
	return (((float)1 - t) * (t_vec4){1, 1, 1, 0} + t * (t_vec4){0.5, 0.7, 1.0, 0});
}

t_vec4 ray_at(t_ray r, float t)
{
	return (r.orig + (t * r.dir));
}

t_ray ray_init(t_vec4 o, t_vec4 d)
{
	t_ray	r;
	r.orig = o;
	r.dir = d;
	return (r);
}

t_ray	get_ray(t_cam cam, float u, float v)
{
	return (ray_init(cam.orig, cam.btm_left_cnr + (u * cam.horiz) + (v * cam.vert) - cam.orig));
}
