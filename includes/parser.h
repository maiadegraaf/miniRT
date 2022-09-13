/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 12:33:28 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/13 13:03:45 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minirt.h"

// parser
t_elements		parse_input(char *file);

// parser utils
int				check_file_type(char *input);
t_tokens		return_type(char *s);
char			*read_float(char *line, float *o, float min, float max);
char			*read_vec4(char *line, t_vec4 *o, float min, float max);
char			*skip_spaces(char *s);

// chunk utils
char			*find_next_chunk(char *line);
char 			*line_to_chunk(char *line);

// parse vec4
int				ctovec4(char *s, t_vec4 *vec4);

//ambient
t_ambient		*ambient_assign(char *line);

//camera
t_cam			*cam_assign(char *line);

//light
t_point_light	*point_light_assign(char *line);

//object
int				*hittable_lst_assign(char *line, t_tokens t, t_hittable_lst **objs);

#endif // PARSER_H