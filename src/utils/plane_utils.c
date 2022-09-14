/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:00:02 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 11:42:56 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plane.h"

t_plane	*plane_init(t_vec4 point, t_vec4 vector)
{
	t_plane *p;
	
	p = malloc(sizeof(t_plane));
	if (!p)
		ft_error(10);
	p->point = point;
	p->vector = vector;
	return (p);
}