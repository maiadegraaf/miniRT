/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:57:57 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:56:34 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

t_cylinder	*cylinder_init(t_vec4 center, t_vec4 orientation,
	float diameter, float height)
{
	t_cylinder	*c;

	c = malloc(sizeof(t_cylinder));
	if (!c)
		ft_error(10);
	c->center = center;
	c->orientation = orientation;
	c->diameter = diameter;
	c->height = height;
	return (c);
}
