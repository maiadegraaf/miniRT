/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 14:34:21 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 15:39:01 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H
# include "minirt.h"
# include "hittable.h"

typedef struct s_hittable	t_hittable;

typedef struct s_sphere
{
	t_vec4		center;
	float		radius;
}	t_sphere;

t_sphere	*sphere_init(t_vec4 center, float radius);
bool		sphere_hit(t_hittable hit, t_sphere *s);

#endif // SPHERE_H