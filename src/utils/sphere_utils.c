/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 14:44:26 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/26 13:41:33 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere	sphere_init(t_vec3 cen, double r)
{
	t_sphere	sphere;

	sphere.cen = cen;
	sphere.r = r;
	sphere.hit = sphere_hit;
	return (sphere);
}

bool	sphere_hit(t_hittable *hit, t_sphere *sphere)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	disc;
	double	sqrtd;
	double	root;
	t_vec3	outward_normal;

	oc = vec3_sub(hit->r.origin, sphere->cen);
	a = length_sqrd(hit->r.direction);
	half_b = dot(oc, hit->r.direction);
	c = length_sqrd(oc) - (sphere->r * sphere->r);
	disc = (half_b * half_b) - (a * c);
	if (disc < 0)
		return (false);
	sqrtd = sqrt(disc);
	root = (-half_b - sqrtd) / a;
	if (root < hit->t_min || root > hit->t_max)
	{
		root = (-half_b + sqrtd) / a;
		if (root < hit->t_min || root > hit->t_max)
			return (false);
	}
	hit->rec.t = root;
	hit->rec.p = ray_at(hit->r, hit->rec.t);
	outward_normal = vec3_div(sphere->r, vec3_sub(hit->rec.p, sphere->cen));
	set_face_normal(hit->r, outward_normal, &hit->rec);
	return (true);
}

double	hit_sphere(t_vec3 center, double radius, t_ray *r)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	disc;

	oc = vec3_sub(r->origin, center);
	a = length_sqrd(r->direction);
	half_b = dot(oc, r->direction);
	c = length_sqrd(oc) - (radius * radius);
	disc = (half_b * half_b) - (a * c);
	if (disc < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(disc)) / (a));
}
