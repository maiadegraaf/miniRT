/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:34:40 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 14:50:44 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vec4	ray_at(t_ray r, float t)
{
	return (r.orig + (t * r.dir));
}

t_ray	ray_init(t_vec4 o, t_vec4 d)
{
	t_ray	r;

	r.orig = o;
	r.dir = d;
	return (r);
}

t_ray	get_ray(t_cam cam, float i, float j, t_win	win)
{
	float	u;
	float	v;

	u = ((float) i) / (win.w - 1);
	v = ((float) j) / (win.h - 1);
	return (ray_init(cam.orig, cam.btm_left_cnr
			+ (u * cam.horiz) + (v * cam.vert) - cam.orig));
}
