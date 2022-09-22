/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_record_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:14:48 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/22 12:14:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_hit_record	*hit_rec_init_empty(void)
{
	t_hit_record	*rec;

	rec = malloc(sizeof(t_hit_record));
	if (!rec)
		ft_error(10);
	rec->p = (t_vec4){0};
	rec->n = (t_vec4){0};
	rec->t = 0;
	rec->front_face = false;
	return (rec);
}

void	set_face_normal(t_hit_record *rec, const t_ray r,
	const t_vec4 outward_normal)
{
	rec->front_face = dot(r.dir, outward_normal) < 0;
	if (rec->front_face)
		rec->n = outward_normal;
	else
		rec->n = -outward_normal;
}
