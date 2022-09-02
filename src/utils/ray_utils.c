/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:34:40 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/02 10:17:02 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"


t_vec4 ray_color(t_ray r)
{
	t_vec4	unit_dir;
	float	t;
	t_vec4	n;

	t = hit_sphere((t_vec4){0, 0, -1, 0}, 0.5, r);
	if (t > (float)0)
	{
		n = unit_vector(ray_at(r, t) - (t_vec4){0, 0, -1, 0});
		n = (float)0.5 * (n + (float)1.0);
		printf("{%f, %f, %f}\n", n[0], n[1], n[2]);
		return (n);
	}
	unit_dir = unit_vector(r.dir);
	t = (float)0.5 * (unit_dir[1] + (float)1.0);
	return (((float)1 - t) * (t_vec4){1, 1, 1, 0} + t * (t_vec4){0.5, 0.7, 1.0, 0});
}

t_vec4 ray_at(t_ray r, float t)
{
	return (r.orig + (t * r.dir));
}

t_ray ray_init(t_vec4 o, t_vec4 d)
{
	t_ray	r;
	r.orig = o;
	r.dir = d;
	return (r);
}