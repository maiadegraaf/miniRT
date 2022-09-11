/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:20:52 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 17:23:36 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_file_type(char *input)
{
	char	**split;
	int		i;

	i = 0;
	if (!ft_strchr(input, '.'))
		ft_error(0);
	split = ft_split(input, '.');
	if (ft_strncmp("rt", split[1], ft_strlen(split[1])))
		i++;
	free_arr(split);
	if (i != 0)
		ft_error(0);
	return (i);
}

t_tokens	return_type(char *s)
{
	t_tokens	t;
	t = 0;
	if (!ft_strncmp(s, "A", ft_strlen(s)))
		t = A;
	else if (!ft_strncmp(s, "C", ft_strlen(s)))
		t = C;
	else if (!ft_strncmp(s, "L", ft_strlen(s)))
		t = L;
	else if (!ft_strncmp(s, "sp", ft_strlen(s)))
		t = SP;
	else if (!ft_strncmp(s, "pl", ft_strlen(s)))
		t = PL;
	else if (!ft_strncmp(s, "cy", ft_strlen(s)))
		t = CY;
	else
	{
		ft_printf("%s", s);
		ft_error(2);
	}
	free(s);
	return (t);
}

int	chunk_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	return (i);
}

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

char	*find_next_chunk(char *line)
{
	line = skip_spaces(line);
	while(line && *line != ' ')
		line++;
	return (line);
}
