/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:36:47 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/16 12:39:47 by fpolycar      ########   odam.nl         */
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

float	set_discriminant(float a, float half_b, float c)
{
	return (half_b * half_b - a * c);
}

bool	sphere_hit(t_hittable hit, t_sphere *s)
{
	t_vec4	oc;
	float	a;
	float	half_b;
	float	discriminant;
	float	sqrtd;

	oc = hit.r->orig - s->center;
	a = length_squared(hit.r->dir);
	half_b = dot(oc, hit.r->dir);
	discriminant = set_discriminant(a, half_b,
			length_squared(oc) - (s->radius * s->radius));
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	hit.rec->t = (-half_b - sqrtd) / a;
	if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
	{
		hit.rec->t = (-half_b + sqrtd) / a;
		if (hit.rec->t < hit.t_min || hit.t_max < hit.rec->t)
			return (false);
	}
	hit.rec->p = ray_at(*hit.r, hit.rec->t);
	set_face_normal(hit.rec, *hit.r, (hit.rec->p - s->center) / s->radius);
	return (true);
}
