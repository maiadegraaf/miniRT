/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:38 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 16:50:52 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_point_light point_light_init(t_vec4	position, t_vec4 color, float power)
{
	t_point_light	node;

	node.position = position;
	node.diff_color = color;
	node.diff_power = power;
	node.spec_color = (t_vec4){1, 1, 1, 1};
	node.spec_power = 2;
	return (node);
}

t_point_light *point_light_assign(char *line)
{
	t_point_light	*new = NULL;
	(void) line;
	return (new);
}
