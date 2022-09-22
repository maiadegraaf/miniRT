/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder_faces_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fpolycar <fpolycar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:21:22 by fpolycar      #+#    #+#                 */
/*   Updated: 2022/09/22 15:01:32 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder.h"

bool	cylinder_cap_bottom(t_hittable hit, t_cylinder *cyl)
{
	t_plane			*plane;

	plane = plane_init(cyl->center, cyl->n);
	if (plane_hit(hit, plane)
		&& length(hit.rec->p - plane->point) <= cyl->radius)
	{
		if (dot(hit.rec->n, cyl->n) > 0)
			hit.rec->n = (t_vec4){0, 0, 0};
		free(plane);
		return (true);
	}
	free(plane);
	return (false);
}

bool	cylinder_cap_top(t_hittable hit, t_cylinder *cyl)
{
	t_plane			*plane;

	plane = plane_init(cyl->center + (cyl->n * cyl->height), cyl->n);
	if (plane_hit(hit, plane)
		&& length(hit.rec->p - plane->point) <= cyl->radius)
	{
		if (dot(hit.rec->n, cyl->n) < 0)
			hit.rec->n = (t_vec4){0, 0, 0};
		free(plane);
		return (true);
	}
	free(plane);
	return (false);
}

bool	send_shape_cylinder(t_hittable hit, t_cylinder *cyl, int index)
{
	if (!cyl)
		return (false);
	if (index == 0)
		return (cylinder_hit_shape(hit, cyl));
	if (index == 1)
		return (cylinder_cap_top(hit, cyl));
	if (index == 2)
		return (cylinder_cap_bottom(hit, cyl));
	return (false);
}

int	cylinder_hittable(t_hittable hit, t_cylinder *cyl)
{
	double			closest_so_far;
	int				i;
	int				closest_index;

	i = 0;
	closest_index = -1;
	closest_so_far = hit.t_max;
	while (i < 3)
	{
		if (send_shape_cylinder(hit, cyl, i))
		{
			if (hit.rec->t < closest_so_far)
			{
				closest_so_far = hit.rec->t;
				closest_index = i;
			}
		}
		i++;
	}
	return (closest_index);
}

bool	cylinder_hit(t_hittable hit, t_cylinder *cyl)
{
	int	index;

	index = cylinder_hittable(hit, cyl);
	if (index == -1)
		return (false);
	return (send_shape_cylinder(hit, cyl, index));
}
