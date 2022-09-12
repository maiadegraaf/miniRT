/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ambient.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:44 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/12 10:02:21 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ambient *ambient_assign(char *line)
{
	t_ambient	*new;

	new = malloc(sizeof(t_ambient));
	if (!new)
		ft_error(10);
	line = read_float(line, &new->strength, 0, 1);
	line = read_vec4(line, &new->color, 0, 255);
	return (new);
}