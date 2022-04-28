/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 15:08:33 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/26 14:21:12 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_ray r, t_vec3 outward_norm, t_hit_record *rec)
{
	rec->front_face = dot(r.direction, outward_norm) < 0;
	if (rec->front_face)
		rec->normal = outward_norm;
	else
		rec->normal = vec3_neg(outward_norm);
}

t_hittable	hittable_init(t_ray r, double t_min, double t_max, t_hit_record rec)
{
	t_hittable	new;

	new.r = r;
	new.t_min = t_min;
	new.t_max = t_max;
	new.rec = rec;
	return (new);
}

t_hit_record	hit_rec_init_empty(void)
{
	t_hit_record rec;

	rec.p = vec3_init(0, 0, 0);
	rec.normal = vec3_init(0, 0, 0);
	rec.t = 0.0;
	rec.front_face = false;
	return (rec);
}