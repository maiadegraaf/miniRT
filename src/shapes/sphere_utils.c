/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:36:47 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/22 13:52:16 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_sphere	*sphere_init(t_vec4 center, float radius)
{
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (!s)
		ft_error(10);
	s->center = center;
	s->radius = radius;
	return (s);
}

bool	sphere_hit(t_hittable hit, t_sphere *s)
{
	t_vec4	oc;
	t_abc	abc;
	float	discriminant;
	float	sqrtd;

	oc = hit.r->orig - s->center;
	abc.a = length_squared(hit.r->dir);
	abc.b = dot(oc, hit.r->dir);
	abc.c = length_squared(oc) - (s->radius * s->radius);
	discriminant = abc.b * abc.b - abc.a * abc.c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	hit.rec->t = (-abc.b - sqrtd) / abc.a;
	if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
	{
		hit.rec->t = (-abc.b + sqrtd) / abc.a;
		if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
			return (false);
	}
	hit.rec->p = ray_at(*hit.r, hit.rec->t);
	set_face_normal(hit.rec, *hit.r, (hit.rec->p - s->center) / s->radius);
	return (true);
}
