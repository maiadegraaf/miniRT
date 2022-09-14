/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:00:02 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 12:03:13 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane	*plane_init(t_vec4 point, t_vec4 vector)
{
	t_plane *p;
	
	p = malloc(sizeof(t_plane));
	if (!p)
		ft_error(10);
	p->point = point;
	p->vector = vector;
	return (p);
}

bool plane_hit(t_hittable hit, t_plane *p)
{
	t_vec4	substract_ray;
	float	discriminant;

	substract_ray = hit.r->orig - hit.r->dir - p->point;
	discriminant = dot(p->vector, substract_ray);
	if (discriminant == 0)
		return true;
	return (false);
}