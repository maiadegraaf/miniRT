/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:40:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/02 16:33:45 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable.h"

t_hittable	hittable_init(t_ray *r, float t_min, float t_max, t_hit_record *rec)
{
	t_hittable 		h;

	h.r = r;
	h.t_min = t_min;
	h.t_max = t_max;
	h.rec = rec;
	return (h);
}