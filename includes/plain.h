/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plain.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:37 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/12 10:49:41 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAIN_H
# define PLAIN_H
# include "minirt.h"

typedef struct	s_plain
{
	t_vec4	center;
	t_vec4	orientation;
} t_plain;

#endif // PLAIN_H