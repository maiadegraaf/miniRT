/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:57:57 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/22 14:34:10 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

float	cylinder_infinate(t_hittable hit, t_cylinder *cyl)
{
	t_abc	abc;
	t_ray	rray;
	float	t;
	float	y;

	rray.orig = hit.r->orig - cyl->center;
	rray.orig = rodrigues(rray.orig, cyl->axis, cyl->angle);
	rray.dir = rodrigues(hit.r->dir, cyl->axis, cyl->angle);
	abc.a = rray.dir[0] * rray.dir[0] + rray.dir[2] * rray.dir[2];
	abc.b = 2 * (rray.dir[0] * rray.orig[0] + rray.dir[2] * rray.orig[2]);
	abc.c = rray.orig[0] * rray.orig[0] + rray.orig[2] * rray.orig[2]
		- pow(cyl->radius, 2);
	t = quadratic(abc);
	if (t < 0)
		return (-1);
	y = rray.orig[1] + t * rray.dir[1];
	if (y < 0 || y > cyl->height)
		return (-1);
	return (t);
}

t_vec4	cylinder_center(t_cylinder *cyl, t_vec4 point)
{
	float	x;

	x = dot(point - cyl->center, cyl->n);
	return (point - (x * cyl->n + cyl->center));
}

bool	cylinder_hit_shape(t_hittable hit, t_cylinder *cyl)
{
	hit.rec->t = cylinder_infinate(hit, cyl);
	if (hit.rec->t >= 0)
	{
		hit.rec->p = ray_at(*hit.r, hit.rec->t);
		hit.rec->n = unit_vector(cylinder_center(cyl, hit.rec->p));
		if (length(cylinder_center(cyl, hit.r->orig)) < cyl->radius)
			hit.rec->n = (t_vec4){0, 0, 0};
		return (true);
	}
	return (false);
}
