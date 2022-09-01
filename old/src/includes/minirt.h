/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:41:03 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/08/31 16:11:58 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# define ASPECT_RATIO (16.0 / 9.0)

// ray generation: 
// ray.x = u / width - 0.5
// ray.y = v / height - 0.5
// ray.z = 1

// generate lookAt (forward, right, up)

// rotated ray = multiply lookat by ray


typedef struct s_sphere	t_sphere;

typedef float t_vec4 __attribute__ ((vector_size (16)));

typedef enum s_tokens
{
	SPHERE = 1,
}	t_tokens;

mlx_image_t	*g_img;

typedef struct s_mlx_win
{
	int	width;
	int	height;
	int	x;
	int	y;
}	t_mlx_win;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_cam
{
	float	vp_h;
	float	vp_w;
	float	foc_l;
	t_vec4	origin;
	t_vec4	hor;
	t_vec4	vert;
	t_vec4	btm_l_corner;
}	t_cam;

typedef struct s_ray
{
	t_vec4	origin;
	t_vec4	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_vec4	p;
	t_vec4	normal;
	float	t;
	bool	front_face;
}	t_hit_record;

typedef struct s_hittable
{
	t_ray			r;
	float			t_min;
	float			t_max;
	t_hit_record	rec;
}	t_hittable;

typedef struct s_sphere
{
	t_vec4		cen;
	float		r;
	bool		(*hit)(t_hittable *, t_sphere *);
}	t_sphere;

	// t_hittable	hittable;
typedef struct s_hittable_lst
{
	t_sphere				sphere;
	t_tokens				shape;
	t_vec4					color;
	struct s_hittable_lst	*next;
}	t_hittable_lst;

typedef struct s_lighting
{
	t_vec4	diffuse;
	t_vec4	specular;
}	t_lighting;

typedef struct s_p_light
{
	t_vec4	position;
	t_vec4	diffuse_color;
	float	diffuse_power;
	t_vec4	specular_color;
	float	specular_power;
}	t_p_light;



//vec3_utils
float			length_sqrd(t_vec4 v);
float			length(t_vec4 v);
t_vec4			unit_vector(t_vec4 v);
t_vec3			vec3_neg(t_vec3 v);
t_vec3			vec3_init(float x, float y, float z);

//vec3_dot_cross
float			dot(t_vec4 u, t_vec4 v);
t_vec4			cross(t_vec4 u, t_vec4 v);

//ray_utils
t_vec4			ray_at(t_ray ray, float t);
t_ray			ray_init(t_vec4 origin, t_vec4 direction);
t_ray			get_ray(t_cam cam, float u, float v);
t_vec4			ray_color(t_ray *ray, t_hittable_lst *world, int depth);

//sphere_utils
bool			sphere_hit(t_hittable *hit, t_sphere *sphere);
t_sphere		sphere_init(t_vec4 cen, float r);
float			hit_sphere(t_vec4 center, float radius, t_ray *r);

//hit_utils
void			set_face_normal(t_ray r, t_vec4 outward_norm,
			t_hit_record *rec);
t_hittable		hittable_init(t_ray r, float t_min, float t_max,
			t_hit_record rec);
t_hit_record	hit_rec_init_empty(void);

//hittable_list_utils
t_hittable_lst	*hittable_lst_new(t_sphere sphere, t_tokens shape, t_vec4 color);
t_hittable_lst	*hittable_lst_add_back(t_hittable_lst **lst,
					t_hittable_lst *new);

//utils
int				create_rgba(int r, int g, int b, int a);
void			write_color(t_vec4 color, t_mlx_win *win, int samples_per_pixel);
float			deg_to_rad(float deg);
float			clamp(float x, float min, float max);

#endif