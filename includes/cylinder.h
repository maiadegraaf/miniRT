/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 10:22:24 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/22 14:53:13 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "minirt.h"

typedef float	t_vec4 __attribute__ ((vector_size (16)));

typedef struct s_cylinder
{
	t_vec4	center;
	t_vec4	n;
	float	radius;
	float	height;
	float	angle;
	t_vec4	axis;
}	t_cylinder;

float	cylinder_infinate(t_hittable hit, t_cylinder *cyl);
t_vec4	cylinder_center(t_cylinder *cyl, t_vec4 point);
bool	cylinder_hit_shape(t_hittable hit, t_cylinder *cyl);
bool	cylinder_hit(t_hittable hit, t_cylinder *cyl);
int		cylinder_hittable(t_hittable hit, t_cylinder *cyl);
bool	send_shape_cylinder(t_hittable hit, t_cylinder *cyl, int index);
bool	cylinder_cap_top(t_hittable hit, t_cylinder *cyl);
bool	cylinder_cap_bottom(t_hittable hit, t_cylinder *cyl);

#endif // CYLINDER_H