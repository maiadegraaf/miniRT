/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 12:28:29 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 15:33:33 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	assign_element(char *line, t_tokens t, t_elements *element)
{
	if (t == A)
	{
		if (element->ambient == NULL)
			element->ambient = ambient_assign(line);
		else
			ft_error(21);
	}
	else if (t == C)
	{
		if (element->cam == NULL)
			element->cam = cam_assign(line);
		else
			ft_error(22);
	}
	else if (t == L)
	{
		if (element->light == NULL)
			element->light = point_light_assign(line);
		else
			ft_error(23);
	}
	else if (t == SP || t == PL || t == CY)
		element->objs = hittable_lst_assign(line, t);
} 

t_elements	parse_input(char *file)
{
	t_elements	elements;
	char		*line;
	int			fd;

	check_file_type(file);
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		ft_error(1);
	elements = elements_init_empty();
	while (line)
	{
		assign_element(line, 
			return_type(line_to_chunk(line)), &elements);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (elements);
}