/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:20:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/08 17:51:41 by fpolycar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

// bool world_in_order(t_hittable_lst world)
// {
// 	while (world)
// 	{
// 		if (D object-light < D1 object-light)
// 			return (false);
// 	}
// 	return(true);
// }

// t_hittable_lst closest_(t_hittable_lst *world, t_hittable light_hit)
// {
// 	while (world_in_order(world) != true)
// 	{
// 		while (world)
// 		{
// 			if (D object-light < D1 object-light)
// 			{
// 				//get min_t ray
				
// 			}
// 			world = world->next;
// 		}
// 		while (world->prev != NULL)
// 			world = world->prev;
// 	}
// }

t_hittable_lst	*find_shadow_touched_first(t_ray r, int index, t_hittable_lst *world)
{
	t_hittable		hit;
	float	tmp_t;
	int	i;
	t_hittable_lst	*start;
	int 			j;
	bool			ret;

	index = 2;
	hit = hittable_init(&r, 0, INFINITY, hit_rec_init_empty());
	i = 0;
	j = 0;
	start = world;
	tmp_t = INFINITY;
	ret = false;
	while (start)
	{
		if (start->i != index && hit_hittable_list(hit, start))
		{
			if (hit.rec->t < tmp_t)
			{
				tmp_t = hit.rec->t;
				i = j;
			}
			ret = true;
		}
		j++;
		start = start->prev;
	}
	j = i;
	while (i != 0 && world && j > 0)
	{
		world = world->next;
		j--;
	}
	if (ret == true)
		return (world);
	return (NULL);
}

t_point_light point_light_init(t_vec4	position, t_vec4 color, float power)
{
	t_point_light	node;

	node.position = position;
	node.diff_color = color;
	node.diff_power = power;
	node.spec_color = (t_vec4){1, 1, 1, 1};
	node.spec_power = 2;
	return (node);
}

void	check_shadow(t_hittable_lst *world, t_ray light_r, t_lighting *l, t_vec4 l_color, float distance)
{
	t_hittable light_hit;

	world = find_shadow_touched_first(light_r, world->i, ft_hittable_lstlast(world));
	light_hit = hittable_init(&light_r, 0, INFINITY, hit_rec_init_empty());
	if (world && hit_hittable_list(light_hit, world))
	{
		l->if_s = true;
		// float	intensity = -((distance - light_hit.rec->t)/200 - hit_sphere(world->s, *light_hit.r)) / 50;
		float intensity = clamp(dot(light_hit.rec->n, -light_hit.r->dir), 0, 1);
		// printf("intenstiy = %f\n", intensity);
		// (void) distance;
		l->shadow = world->color / (1 - intensity * l_color / distance);
		l->shadow[0] = clamp(l->shadow[0], 0, l->diff[0] + l->spec[0]);
		l->shadow[1] = clamp(l->shadow[1], 0, l->diff[1] + l->spec[1]);
		l->shadow[2] = clamp(l->shadow[2], 0, l->diff[2] + l->spec[2]);
	}
}

t_lighting get_point_light(t_point_light light, t_hittable hittable, t_hittable_lst *world)
{
	t_lighting	l;
	t_vec4		light_dir;
	float		distance;
	float		intensity;
	t_vec4		h;

	l.diff = (t_vec4){0, 0, 0, 0};
	l.spec = (t_vec4){0, 0, 0, 0};
	l.if_s = false;
	if (light.diff_power > 0)
	{
		light_dir = light.position - hittable.rec->p;
		distance = length(light_dir);
		light_dir = unit_vector(light_dir);
		distance *= distance;
		intensity = clamp(dot(hittable.rec->n, light_dir), 0, 1);
		l.diff = world->color * intensity * light.diff_color * light.diff_power / distance;
		h = unit_vector(-light_dir + hittable.r->dir);
		intensity = pow((float)dot(hittable.rec->n, h), 120);
		l.spec = intensity * light.spec_color / distance;
		check_shadow(world, ray_init(light.position, -light_dir), &l, light.diff_color, distance);
	}
	return (l);
}