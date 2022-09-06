/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:34:40 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/06 14:07:19 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec4 ray_color(t_ray r, t_hittable_lst *world)
{
	t_vec4			unit_dir;
	float			t;
	t_hit_record	rec;
	t_hittable		hit;

	hit = hittable_init(&r, 0, INFINITY, &rec);
	if (hit_hittable_list(hit, world))
		return (0.5 * (rec.n + (t_vec4){1, 1, 1, 0}));
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