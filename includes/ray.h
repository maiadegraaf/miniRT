/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:31:15 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/08/31 18:10:09 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "minirt.h"

typedef struct s_ray
{
	t_vec4	orig;
	t_vec4	dir;
} t_ray;

t_vec4 ray_at(t_ray r, float t);
t_ray ray_init(t_vec4 o, t_vec4 d);
t_vec4 ray_color(t_ray r);

#endif // RAY_H