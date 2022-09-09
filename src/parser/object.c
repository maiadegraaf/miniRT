/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:31 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 14:18:59 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	create_obj(t_hittable_lst **world, t_sphere *sphere, t_vec4 color)
{
	t_hittable_lst	*node;

	node = ft_hittable_lstnew(sphere, color);
	if (!node)
		perror("malloc ");
	ft_hittable_lstadd_back(world, node);
}

t_hittable_lst	*hittable_lst_assign(char *list, t_tokens t)
{
	
}