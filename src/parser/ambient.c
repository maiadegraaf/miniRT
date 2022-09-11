/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ambient.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:44 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 17:05:35 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ambient *ambient_assign(char *line)
{
	t_ambient	*new;
	char		*line_tmp;
	float		f;
	t_vec4		vec4;

	new = malloc(sizeof(t_ambient));
	line_tmp = find_next_chunk(line);
	if (!line_tmp)
		ft_error(4);
	
	if (ctof(line_to_chunk(line_tmp), &f))
	{
		ft_printf("Float conversion impossiblein line: '%s'\n", line);
		ft_error(-1);
	}
	if (f < 0 || f > 1.0)
		ft_error(3);
	new->strength = f;
	line_tmp = find_next_chunk(line_tmp);
	if (!line_tmp)
		ft_error(4);
	if (ctovec4(line_to_chunk(line_tmp), &vec4))
	{
		ft_printf("Vec3 conversion impossiblein line: '%s'\n", line);
		ft_error(-1);
	}
	new->color = vec4;
	return (new);
}