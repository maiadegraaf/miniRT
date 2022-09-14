/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:24 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 15:48:41 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "minirt.h"

typedef float	t_vec4 __attribute__ ((vector_size (16)));

typedef struct s_cylinder
{
	t_vec4	center;
	t_vec4	orientation;
	float	diameter;
	float	height;
}	t_cylinder;

#endif // CYLINDER_H