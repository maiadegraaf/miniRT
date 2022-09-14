/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:38 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:00:40 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_point_light	*point_light_assign(char *line)
{
	t_point_light	*new;

	new = malloc(sizeof(t_point_light));
	if (!new)
		ft_error(10);
	line = read_vec4(line, &new->position, 1, 0);
	line = read_float(line, &new->diff_power, 0, 1);
	line = read_vec4(line, &new->diff_color, 0, 255);
	new->diff_color /= 255;
	new->spec_color = (t_vec4){1, 1, 1, 1};
	new->spec_power = 1;
	return (new);
}
