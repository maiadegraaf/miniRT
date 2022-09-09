/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec4_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 15:46:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 16:02:37 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ctovec4(char *s, t_vec4 *vec4)
{
	float	x;
	float	y;
	float	z;
	char	**split;

	split = ft_split(s, ',');
	if (!split || ft_strlen(*split) != 3)
		return(EXIT_FAILURE);
	if (ctof(read_comma(split[0]), &x) || ctof(read_comma(split[1]), &x)
		|| ctof(read_comma(split[2]), &x))
		return(EXIT_FAILURE);
	*vec4 = (t_vec4){x, y, z, 0};
	return (EXIT_SUCCESS);
}