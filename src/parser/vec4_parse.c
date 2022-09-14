/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec4_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 15:46:39 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:56:29 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_rows(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	ctovec4(char *s, t_vec4 *vec4)
{
	float	x;
	float	y;
	float	z;
	char	**split;

	x = 0;
	y = 0;
	z = 0;
	split = ft_split(s, ',');
	if (!split || count_rows(split) != 3)
		return (EXIT_FAILURE);
	if (ctof(split[0], &x) || ctof(split[1], &y)
		|| ctof(split[2], &z))
		return (EXIT_FAILURE);
	*vec4 = (t_vec4){x, y, z, 0};
	return (EXIT_SUCCESS);
}
