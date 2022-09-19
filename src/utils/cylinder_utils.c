/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:57:57 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/19 12:53:10 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_cylinder	*cylinder_init(t_vec4 center, t_vec4 orientation,
	float diameter, float height)
{
	t_cylinder	*c;

	c = malloc(sizeof(t_cylinder));
	if (!c)
		ft_error(10);
	c->center = center;
	c->orientation = orientation;
	c->diameter = diameter;
	c->height = height;
	return (c);
}


bool cylinder_hit(t_hittable hit, t_cylinder *cyl)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vec4	e;
	t_vec4	f;

	e = hit.r->dir - (dot(hit.r->dir, cyl->orientation) / dot(cyl->orientation, cyl->orientation))*cyl->orientation;
	f = (hit.r->orig - cyl->center) - (dot(hit.r->orig - cyl->center, cyl->orientation)/ dot(cyl->orientation, cyl->orientation))*cyl->orientation;
	a = dot(e,e);
	b = 2*dot(e,f);
	c = dot(f,f) - pow((cyl->diameter / 2), 2);
	delta = pow(b, 2) - 4*a*c;
	hit.rec->t = (-b - sqrt(delta)) / (2*a);
	if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
	{
		hit.rec->t = (-b + sqrt(delta)) / (2*a);
		if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
			return (false);
	}
	hit.rec->p = ray_at(*hit.r, hit.rec->t);
	// float height_point;
	// height_point = cyl->height / sqrt(pow(fabs(cyl->orientation[1]), 2));
	// if (hit.rec->p[1] > cyl->center[1] + height_point || hit.rec->p[1] < cyl->center[1] + height_point)
	// 	return (false);
	set_face_normal(hit.rec, *hit.r, (hit.rec->p - (cyl->center + hit.rec->p * cyl->orientation)));
	return (true);
}
