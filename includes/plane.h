/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:37 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/15 14:13:37 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "minirt.h"

typedef struct s_plane
{
	t_vec4	point;
	t_vec4	vector;
} t_plane;

#endif