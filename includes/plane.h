/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:37 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:40:34 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "minirt.h"

typedef struct s_plane
{
	t_vec4	center;
	t_vec4	orientation;
}	t_plane;

#endif // PLANE_H