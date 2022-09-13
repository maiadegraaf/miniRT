/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plain.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:37 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/13 13:21:25 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef plane_H
# define plane_H
# include "minirt.h"

typedef struct	s_plane
{
	t_vec4	center;
	t_vec4	orientation;
} t_plane;

#endif // plane_H