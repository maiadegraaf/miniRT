/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_list_create_utils.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:57:49 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 14:58:09 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_lst.h"

t_hittable_lst	*ft_hittable_lstnew(t_sphere *s, t_plane *p,
	t_cylinder *c, t_vec4 color)
{
	t_hittable_lst	*new_element;
	static int		i = 0;

	new_element = (t_hittable_lst *)malloc(sizeof(t_hittable_lst));
	if (!new_element)
		return (0);
	new_element->s = s;
	new_element->p = p;
	new_element->c = c;
	new_element->color = color;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_hittable_lstadd_back(t_hittable_lst **lst, t_hittable_lst *new)
{
	t_hittable_lst	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
