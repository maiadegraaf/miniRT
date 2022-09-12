/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plain_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:00:02 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/12 11:28:26 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "plain.h"

t_plain	*plain_init(t_vec4 center, t_vec4 orientation)
{
	t_plain *p;
	
	p = malloc(sizeof(t_plain));
	if (!p)
		ft_error(10);
	p->center = center;
	p->orientation = orientation;
	return (p);
}