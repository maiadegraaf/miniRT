/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:36:47 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/08 12:32:44 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sphere.h"

t_sphere	*sphere_init(t_vec4 center, float radius)
{
	t_sphere *s;
	
	s = malloc(sizeof(t_sphere));
	if (!s)
		perror("OH NO!!\n");
	s->center = center;
	s->radius = radius;
	return (s);
}

bool sphere_hit(t_hittable hit, t_sphere *s)
{
	t_vec4	oc;
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	t_vec4	outward_normal;

	oc = hit.r->orig - s->center;
	a = length_squared(hit.r->dir);
	half_b = dot(oc, hit.r->dir);
	c = length_squared(oc) - (s->radius * s->radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	hit.rec->root2 = 0;
	if (root < hit.t_min || hit.t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		hit.rec->root2 = (-half_b + sqrtd) / a;
		if (root < hit.t_min || hit.t_max < root)
			return (false);
	}
	hit.rec->t = root;
	hit.rec->p = ray_at(*hit.r, hit.rec->t);
	outward_normal = (hit.rec->p - s->center) / s->radius;
	set_face_normal(hit.rec, *hit.r, outward_normal);
	return (true);
}