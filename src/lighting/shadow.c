/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 16:06:17 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/22 13:35:17 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

bool	find_object_in_front(t_hittable light_hit, t_ray r,
	t_hittable_lst *world)
{
	t_hittable		hit;
	float			tmp_t;
	t_hittable_lst	*start;

	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	start = ft_hittable_lstlast(world);
	hit_hittable_list(light_hit, world);
	tmp_t = light_hit.rec->t;
	while (start)
	{
		if (hit_hittable_list(hit, start))
		{
			if (hit.rec->t < tmp_t)
			{
				free (hit.rec);
				return (true);
			}
		}
		start = start->prev;
	}
	free (hit.rec);
	return (false);
}

void	check_shadow(t_hittable_lst *world, t_ray light_r, t_lighting *l)
{
	t_hittable	light_hit;

	light_hit = hittable_init(&light_r, 0, INFINITY, hit_rec_init_empty());
	if (find_object_in_front(light_hit, light_r, world))
		l->if_s = true;
	free (light_hit.rec);
}
