/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:57:57 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/21 15:23:05 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

// t_cylinder	*cylinder_init(t_vec4 center, t_vec4 n,
// 	float diameter, float height)
// {
// 	t_cylinder	*c;

// 	c = malloc(sizeof(t_cylinder));
// 	if (!c)
// 		ft_error(10);
// 	c->center = center;
// 	c->n = n;
// 	c->diameter = diameter;
// 	c->height = height;
// 	return (c);
// }

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

bool	cylinder_cap(t_hittable hit, t_cylinder *cyl)
{
	t_plane			*plane;
	t_hit_record	btm;
	t_hit_record	top;

	plane = plane_init(cyl->center, cyl->n);
	btm = *hit_rec_init_empty();
	if (plane_hit(hit, plane))
		btm = *hit.rec;
	plane = plane_init(cyl->center + cyl->n * cyl->height, cyl->n);
	if (plane_hit(hit, plane))
		top = *hit.rec;
	else if (btm.front_face && length(btm.p - plane->point) <= cyl->radius)
	{
		hit.rec = &btm;
		return (true);
	}
	if (btm.t > top.t && length(top.p - plane->point) <= cyl->radius)
		return (true);
	return (false);
}

bool	cylinder_hit(t_hittable hit, t_cylinder *cyl)
{
	hit.rec->t = cylinder_infinate(hit, cyl);
	if (hit.rec->t >= 0)
	{
		hit.rec->p = ray_at(*hit.r, hit.rec->t);
		hit.rec->n = unit_vector(cylinder_center(cyl, hit.rec->p));
		// if (length(cylinder_center(cyl, hit.r->orig)) < cyl->radius)
		// 	hit.rec->n = (t_vec4){0, 0, 0};
		return (true);
	}
	// return(false);
	return (cylinder_cap(hit, cyl));
}
