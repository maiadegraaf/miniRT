/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:31 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 11:43:36 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_sphere	*parse_sphere(char *line, t_vec4 *color)
{
	t_sphere	*new;
	t_vec4		c;

	new = malloc(sizeof(t_sphere));
	if (!new)
		ft_error(10);
	line = read_vec4(line, &new->center, 1, 0);
	line = read_float(line, &new->radius, 1, 0);
	line = read_vec4(line, &c, 0, 255);
	*color = c / 255;
	return (new);
}

t_cylinder *parse_cylinder(char *line, t_vec4 *color)
{
	t_cylinder	*new;
	t_vec4		c;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		ft_error(10);
	line = read_vec4(line, &new->center, 1, 0);
	line = read_vec4(line, &new->orientation, -1, 1);
	line = read_float(line, &new->diameter, 1, 0);
	line = read_float(line, &new->height, 1, 0);
	line = read_vec4(line, &c, 0, 255);
	*color = c / 255;
	return (new);
}

t_plane	*parse_plane(char *line, t_vec4 *color)
{
	t_plane	*new;
	t_vec4	c;

	new = malloc(sizeof(t_plane));
	if (!new)
		ft_error(10);
	line = read_vec4(line, &new->point, 1, 0);
	line = read_vec4(line, &new->vector, -1, 1);
	line = read_vec4(line, &c, 0, 255);
	*color = c / 255;
	return (new);
}

int	*hittable_lst_assign(char *line, t_tokens t, t_hittable_lst **objs)
{
	t_hittable_lst	*node;
	t_vec4			color;
	t_hittable_lst	*tmp;

	node = NULL;
	if (t == SP)
		node = ft_hittable_lstnew(parse_sphere(line, &color), NULL, NULL, color);
	else if(t == PL)
		node = ft_hittable_lstnew(NULL, parse_plane(line, &color), NULL, color);
	// else if (t == CY)
	// 	node = ft_hittable_lstnew(NULL, NULL, parse_cylinder(line, &color), color);
	tmp = *objs;
	ft_hittable_lstadd_back(&tmp, node);
	*objs = tmp;
	return (EXIT_SUCCESS);
}