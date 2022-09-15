/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 09:45:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/15 11:39:53 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	send_shape(t_hittable hit, t_hittable_lst *lst)
{
	if (!lst)
		return(false);
	if (lst->s)
		return(sphere_hit(hit, lst->s));
	else if(lst->p)
		return(plane_hit(hit, lst->p));
	return (false);
}

bool	hit_hittable_list(t_hittable hit, t_hittable_lst *lst)
{
	t_hit_record	tmp_rec;
	bool			hit_anything;
	double			closest_so_far;

	hit_anything = false;
	closest_so_far = hit.t_max;
	if (send_shape(hit, lst))
	{
		hit_anything = true;
		if (tmp_rec.t < closest_so_far)
			closest_so_far = tmp_rec.t;
		hit.rec = &tmp_rec;
	}
	return (hit_anything);
}

float	hit_sphere(t_sphere *s, t_ray r)
{
	t_vec4	oc;
	float	a;
	float	half_b;
	float	c;
	float	disc;

	oc = r.orig - s->center;
	a = length_squared(r.dir);
	half_b = dot(oc, r.dir);
	c = length_squared(oc) - (s->radius * s->radius);
	disc = (half_b * half_b) - (a * c);
	if (disc < 0)
		return (-1.0);
	else
		return ((-half_b - sqrt(disc)) / (a));
}
