/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:00:02 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/16 15:12:05 by fpolycar      ########   odam.nl         */
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
	float denominator;
	float t;
	t_vec4 difference;
	
	denominator = dot(p->vector, hit.r->dir);
	if (fabs(denominator) < 0.0001)
		return (false);
   	difference = p->point - hit.r->orig;
    t = dot(difference, p->vector) / denominator;
	if (t <= 0.0001)
		return (false);
	hit.rec->n = p->vector;
	if (denominator > 0)
		hit.rec->n = p->vector * -1;
	hit.rec->p = ray_at(*hit.r, t);
	hit.rec->t = t;
	set_face_normal(hit.rec, *hit.r, p->vector);
	return (true);
}