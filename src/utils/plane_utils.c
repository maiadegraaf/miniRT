/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plain_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:00:02 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/13 13:21:25 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane	*plane_init(t_vec4 center, t_vec4 orientation)
{
	t_plane *p;
	
	p = malloc(sizeof(t_plane));
	if (!p)
		ft_error(10);
	p->center = center;
	p->orientation = orientation;
	return (p);
}