/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_record_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:14:48 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/02 15:28:38 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

void	set_face_normal(t_hit_record *rec, const t_ray r, const t_vec4 outward_normal)
{
	rec->front_face = dot(r.dir, outward_normal) < 0;
	if (rec->front_face)
		rec->n = outward_normal;
	else
		rec->n = -outward_normal;
}