/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:41:03 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/28 17:11:47 by mgraaf        ########   odam.nl         */
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

typedef struct s_sphere	t_sphere;

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
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_cam
{
	double	vp_h;
	double	vp_w;
	double	foc_l;
	t_vec3	origin;
	t_vec3	hor;
	t_vec3	vert;
	t_vec3	btm_l_corner;
}	t_cam;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_vec3	p;
	t_vec3	normal;
	double	t;
	bool	front_face;
}	t_hit_record;

typedef struct s_hittable
{
	t_ray			r;
	double			t_min;
	double			t_max;
	t_hit_record	rec;
}	t_hittable;

typedef struct s_sphere
{
	t_vec3		cen;
	double		r;
	bool		(*hit)(t_hittable *, t_sphere *);
}	t_sphere;

	// t_hittable	hittable;
typedef struct s_hittable_lst
{
	t_sphere				sphere;
	t_tokens				shape;
	struct s_hittable_lst	*next;
}	t_hittable_lst;

typedef struct s_lighting
{
	t_vec3	diffuse;
	t_vec3	specular;
}	t_lighting;

typedef struct s_p_light
{
	t_vec3	position;
	t_vec3	diffuse_color;
	double	diffuse_power;
	t_vec3	specular_color;
	double	specular_power;
}	t_p_light;



//vec3_utils
double			length_sqrd(t_vec3 v);
double			length(t_vec3 v);
t_vec3			unit_vector(t_vec3 v);
t_vec3			vec3_neg(t_vec3 v);
t_vec3			vec3_init(double x, double y, double z);

//vec3_dot_cross
double			dot(t_vec3 u, t_vec3 v);
t_vec3			cross(t_vec3 u, t_vec3 v);

//vec3_operations
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_sub(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult(t_vec3 a, t_vec3 b);
t_vec3			vec3_mult_d(double t, t_vec3 a);
t_vec3			vec3_div(double t, t_vec3 a);

//ray_utils
t_vec3			ray_at(t_ray ray, double t);
t_ray			ray_init(t_vec3 origin, t_vec3 direction);
t_ray			get_ray(t_cam cam, double u, double v);
t_vec3			ray_color(t_ray *ray, t_hittable_lst *world, int depth);

//sphere_utils
bool			sphere_hit(t_hittable *hit, t_sphere *sphere);
t_sphere		sphere_init(t_vec3 cen, double r);
double			hit_sphere(t_vec3 center, double radius, t_ray *r);

//hit_utils
void			set_face_normal(t_ray r, t_vec3 outward_norm,
			t_hit_record *rec);
t_hittable		hittable_init(t_ray r, double t_min, double t_max,
			t_hit_record rec);
t_hit_record	hit_rec_init_empty(void);

//hittable_list_utils
t_hittable_lst	*hittable_lst_new(t_sphere sphere, t_tokens shape);
t_hittable_lst	*hittable_lst_add_back(t_hittable_lst **lst,
					t_hittable_lst *new);

//utils
int				create_rgba(int r, int g, int b, int a);
void			write_color(t_vec3 *color, t_mlx_win *win, int samples_per_pixel);
double			deg_to_rad(double deg);
double			clamp(double x, double min, double max);

//random_utils
double			rand_double(void);
double			rand_double_min_max(double min, double max);
t_vec3			vec3_random(void);
t_vec3			vec3_random_min_max(double min, double max);
t_vec3			random_in_unit_sphere(void);

#endif