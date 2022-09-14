/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:20:52 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:56:09 by maiadegraaf   ########   odam.nl         */
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
	else if (!ft_strncmp(s, "#", ft_strlen(s)))
		t = '#';
	else
		ft_error_str(5, s);
	free(s);
	return (t);
}

char	*read_float(char *line, float *o, float min, float max)
{
	float	f;

	line = find_next_chunk(line);
	if (!line)
		ft_error(4);
	if (ctof(line_to_chunk(line), &f))
		ft_error_str(2, line);
	if (min < max && (f < min || f > max))
		ft_error_str(3, line);
	*o = f;
	return (line);
}

char	*read_vec4(char *line, t_vec4 *o, float min, float max)
{
	t_vec4	vec4;

	line = find_next_chunk(line);
	if (!line)
		ft_error(4);
	if (ctovec4(line_to_chunk(line), &vec4))
		ft_error_str(1, line);
	if (min < max && (vec4[0] < min || vec4[0] > max
			|| vec4[1] < min || vec4[1] > max
			|| vec4[2] < min || vec4[2] > max))
		ft_error_str(4, line);
	*o = vec4;
	return (line);
}

char	*skip_spaces(char *s)
{
	while (*s && *s == ' ')
		s++;
	return (s);
}
