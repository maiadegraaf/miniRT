/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:37 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 11:41:18 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef plane_H
# define plane_H
# include "minirt.h"

typedef struct	s_plane
{
	t_vec4	point;
	t_vec4	vector;
} t_plane;

#endif // plane_H