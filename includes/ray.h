/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:31:15 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 15:50:08 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "minirt.h"

typedef float					t_vec4 __attribute__ ((vector_size (16)));
typedef struct s_ambient		t_ambient;
typedef struct s_point_light	t_point_light;
typedef struct s_elements		t_elements;
typedef struct s_hittable_lst	t_hittable_lst;
typedef struct s_cam			t_cam;
typedef struct s_win			t_win;

typedef struct s_ray
{
	t_vec4	orig;
	t_vec4	dir;
}	t_ray;

t_vec4			ray_at(t_ray r, float t);
t_ray			ray_init(t_vec4 o, t_vec4 d);
t_vec4			ray_color(t_ray r, t_elements *elements);
t_ray			get_ray(t_cam cam, float i, float j, t_win win);
t_hittable_lst	*find_world_touched_first(t_ray r, t_hittable_lst *world);

#endif // RAY_H