/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_lst_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 15:23:08 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/05/03 15:36:17 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hittable_lst	*hittable_lst_new(t_sphere sphere, t_tokens shape, t_vec4 color)
{
	t_hittable_lst	*node;

	node = malloc(sizeof(t_hittable_lst));
	node->sphere = sphere;
	node->shape = shape;
	node->color = color;
	node->next = NULL;
	return (node);
}

t_hittable_lst	*hittable_lst_add_back(t_hittable_lst **lst,
	t_hittable_lst *new)
{
	t_hittable_lst	*tmp;
	t_hittable_lst	*prev;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return (*lst);
	}
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	tmp->next = new;
	return (*lst);
}

bool	hittable_lst_hit(t_hittable hit, t_hittable_lst *lst)
{
	t_hit_record	tmp_rec;
	bool			hit_anything;
	float			clostest_so_far;

	hit_anything = false;
	clostest_so_far = hit.t_max;
	while (lst)
	{
		if (lst->sphere.hit(&hit, &lst->sphere))
		{
			hit_anything = true;
			clostest_so_far = tmp_rec.t;
			hit.rec = tmp_rec;
		}
		lst = lst->next;
	}
	return (hit_anything);
}
