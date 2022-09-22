/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 09:45:47 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/22 12:01:15 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	send_shape(t_hittable hit, t_hittable_lst *lst)
{
	if (!lst)
		return (false);
	if (lst->s)
		return (sphere_hit(hit, lst->s));
	else if (lst->p)
		return (plane_hit(hit, lst->p));
	else if (lst->c)
		return (cylinder_hit(hit, lst->c));
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
