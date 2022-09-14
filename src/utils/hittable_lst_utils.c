/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_lst_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:49:10 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 14:57:59 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hittable_lst.h"

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
