/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_lst_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:49:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/08 17:42:48 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_lst.h"

t_hittable_lst	*ft_hittable_lstnew(t_sphere *s, t_vec4 color)
{
	t_hittable_lst	*new_element;
	static int		i = 0;

	new_element = (t_hittable_lst *)malloc(sizeof(t_hittable_lst));
	if (!new_element)
		return (0);
	new_element->s = s;
	new_element->color = color;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_hittable_lstadd_back(t_hittable_lst **lst, t_hittable_lst *new)
{
	t_hittable_lst	*tmp;
	// t_hittable_lst	*prev;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		// prev = tmp;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}

void	ft_hittable_lst_rm_first(t_hittable_lst **lst)
{
	t_hittable_lst	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	free(*lst);
	*lst = tmp;
}

void	ft_hittable_lstclear(t_hittable_lst **lst)
{
	t_hittable_lst	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_hittable_lst	*ft_hittable_lstfirst(t_hittable_lst *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
		i++;
	}
	return (map);
}

t_hittable_lst	*ft_hittable_lstlast(t_hittable_lst *map)
{
	int	i;

	i = 0;
	if (!map)
		return (NULL);
	while (map->next != NULL)
	{
		map = map->next;
		i++;
	}
	return (map);
}
