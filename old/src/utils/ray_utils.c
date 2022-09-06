/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 15:01:39 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/06 15:04:38 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	ray_at(t_ray ray, float t)
{
	return (ray.origin + (t * ray.direction));
}

t_ray	ray_init(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	get_ray(t_cam cam, float u, float v)
{
	t_ray	ray;

	ray = ray_init(cam.origin, (cam.btm_l_corner + (u * cam.hor)
				+ (v * cam.vert) - cam.origin));
	return (ray);
}

t_p_light	p_light_init(t_vec4	position, t_vec4 color, float power)
{
	t_p_light	node;

	node.position = position;
	node.diffuse_color = color;
	node.diffuse_power = power;
	node.specular_color = (t_vec4){0, 0, 0, 0};
	node.specular_power = 2;
	return (node);
}

t_lighting	get_point_light(t_p_light light, t_hittable hittable)
{
	t_lighting	out;
	t_vec4		light_dir;
	float		distance;
	float		norm_dot_l;
	float		norm_dot_h;
	float		intensity;
	t_vec4		h;

	out.diffuse = (t_vec4){0};
	out.specular = (t_vec4){0};
	if (light.diffuse_power > 0)
	{
		light_dir = light.position - hittable.rec.p;
		distance = length(light_dir);
		light_dir = unit_vector(light_dir);
		distance = distance * distance;
		norm_dot_l = dot(hittable.rec.normal, light_dir);
		intensity = clamp(norm_dot_l, 0, 1);
		out.diffuse = intensity * light.diffuse_color
			* light.diffuse_power / distance;
		h = unit_vector(light_dir + hittable.r.direction);
		norm_dot_h = dot(hittable.rec.normal, h);
		intensity = pow(clamp(norm_dot_h, 0, 1), 1);
		out.specular = intensity * light.specular_color
			* light.specular_power / distance;
		// if (out.specular.x != 0 || out.specular.y != 0 || out.specular.z != 0)
		// 	printf("specular = (%f, %f, %f)\n", out.specular.x, out.specular.y, out.specular.z);
		// printf("diffuse = (%f, %f, %f)\n", out.diffuse.x, out.diffuse.y, out.diffuse.z);
	}
	return (out);
}

t_vec4	ray_color(t_ray *ray, t_hittable_lst *world, int depth)
{
	t_vec4		unit_direction;
	float		t;
	t_hittable	hittable;
	t_lighting	lighting;

	if (depth <= 0)
		return ((t_vec4){0});
	hittable = hittable_init(*ray, 0, INFINITY, hit_rec_init_empty());
	while (world)
	{
		if (world->sphere.hit(&hittable, &world->sphere))
		{
			lighting = get_point_light(p_light_init((t_vec4){1, 0, 2, 0},
						world->color, 4), hittable);
			return (world->color + lighting.diffuse + lighting.specular);
		}
		world = world->next;
	}
	unit_direction = unit_vector(ray->direction);
	t = (float)0.5 * (unit_direction[1] + (float)1.0);
	return (((float)1 - t) * (t_vec4){1} + t * (t_vec4){0.5, 0.7, 1, 0});
}
