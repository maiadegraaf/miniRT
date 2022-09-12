/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chunk_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 09:34:48 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/12 11:43:20 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	chunk_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

// returns copy of next chunk
char *line_to_chunk(char *line)
{
	char	*chunk;
	size_t	len;

	line = skip_spaces(line);
	len = chunk_len(line);
	chunk = ft_calloc(len, sizeof(char));
	if (!chunk)
		ft_error(10);
	chunk = ft_substr(line, 0, len);
	return (chunk);
}

// returns start of next chunk
char	*find_next_chunk(char *line)
{
	line = skip_spaces(line);
	while(line && *line != ' ')
		line++;
	return (line);
}
