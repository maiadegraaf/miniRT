/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 09:45:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/02 10:00:20 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float hit_sphere(const t_vec4 center, float radius, t_ray r)
{
	t_vec4	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	
	oc = r.orig - center;
	a = dot(r.dir, r.dir);
	b = 2 * dot(oc, r.dir);
	c = dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	else
		return (-b - sqrt(discriminant) / (float)((float)2 * a));
}
