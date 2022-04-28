/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 15:01:39 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/28 18:08:36 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_mult_d(t, ray.direction)));
}

t_ray	ray_init(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	get_ray(t_cam cam, double u, double v)
{
	t_ray	ray;

	ray = ray_init(cam.origin, vec3_sub(vec3_add(cam.btm_l_corner,
					vec3_add(vec3_mult_d(u, cam.hor),
						vec3_mult_d(v, cam.vert))), cam.origin));
	return (ray);
}

t_p_light	p_light_init(t_vec3	position, t_vec3 color, double power)
{
	t_p_light	node;

	node.position = position;
	node.diffuse_color = color;
	node.diffuse_power = power;
	node.specular_color = vec3_init(1, 0, 0);
	node.diffuse_power = power * 2;
	return (node);
}

t_lighting	get_point_light(t_p_light light, t_hittable hittable)
{
	t_lighting	out;
	t_vec3		light_dir;
	double		distance;
	double		norm_dot_l;
	double		norm_dot_h;
	double		intensity;
	t_vec3		h;

	out.diffuse = vec3_init(0, 0, 0);
	out.specular = vec3_init(0, 0, 0);
	if (light.diffuse_power > 0)
	{
		light_dir = vec3_sub(light.position, hittable.rec.p);
		distance = length(light_dir);
		light_dir = unit_vector(light_dir);
		distance = distance * distance;
		norm_dot_l = dot(hittable.rec.normal, light_dir);
		intensity = clamp(norm_dot_l, 0, 1);
		out.diffuse = vec3_mult_d(intensity,
				vec3_mult_d((light.diffuse_power / distance),
					light.diffuse_color));
		h = unit_vector(vec3_add(light_dir, hittable.r.direction));
		norm_dot_h = dot(hittable.rec.normal, h);
		intensity = pow(clamp(norm_dot_h, 0, 1), 0.1);
		out.specular = vec3_mult_d(intensity,
				vec3_mult_d((light.specular_power / distance),
					light.specular_color));
		printf("specular = (%f, %f, %f)\n", out.specular.x, out.specular.y, out.specular.z);
		// printf("diffuse = (%f, %f, %f)\n", out.diffuse.x, out.diffuse.y, out.diffuse.z);
	}
	return (out);
}

t_vec3	ray_color(t_ray *ray, t_hittable_lst *world, int depth)
{
	t_vec3		unit_direction;
	double		t;
	t_hittable	hittable;
	t_lighting	lighting;

	if (depth <= 0)
		return (vec3_init(0, 0, 0));
	hittable = hittable_init(*ray, 0, INFINITY, hit_rec_init_empty());
	while (world)
	{
		if (world->sphere.hit(&hittable, &world->sphere))
		{
			lighting = get_point_light(p_light_init(vec3_init(0, 1, 2),
						vec3_init(0.5, 0.7, 1.0), 5), hittable);
			return (vec3_add(lighting.diffuse, lighting.specular));
			// return (vec3_mult_d(0.5, vec3_add(hittable.rec.normal,
			// 			vec3_init(1, 1, 1))));
		}
		world = world->next;
	}
	unit_direction = unit_vector(ray->direction);
	t = 0.5 * (unit_direction.y + 1.0);
	return (vec3_add(
			vec3_mult_d(1.0 - t, vec3_init(1.0, 1.0, 1.0)),
			vec3_mult_d(t, vec3_init(0.5, 0.7, 1.0))));
}
