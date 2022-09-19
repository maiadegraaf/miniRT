/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:57:57 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/19 17:52:15 by mgraaf        ########   odam.nl         */
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
	hit.rec->p = ray_at(rray, t);
	return (t);
}

t_vec4	cylinder_center(t_cylinder *cyl, t_vec4 point)
{
	t_vec4	center;

	center = cyl->center + (t_vec4){0, point[1], 0};
	// center = point[1] * cyl->center[1];
	// cyl->center *= (t_vec4){1,0,1};
	// center = point - cyl->center;
	return (point - center);
	// return ((t_vec3){point[0] - center[0], 0, 0);
}

bool	cylinder_hit(t_hittable hit, t_cylinder *cyl)
{
	hit.rec->t = cylinder_infinate(hit, cyl);
	if (hit.rec->t >= 0)
	{
		// hit.rec->p = ray_at(*hit.r, hit.rec->t);
		hit.rec->n = unit_vector(cylinder_center(cyl, hit.rec->p));
		
		// set_face_normal(hit.rec, *hit.r, cylinder_center(cyl, hit.rec->p));
		return (true);
	}
	return (false);
}
