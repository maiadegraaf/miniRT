/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:12:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/12 14:56:53 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# include <fcntl.h>
# include <float.h>
# define ASPECT_RATIO (16.0 / 9.0)
# define WIDTH 1200
# define BLACK (t_vec4){0, 0, 0, 0}

typedef float t_vec4 __attribute__ ((vector_size (16)));
typedef struct s_ray t_ray;
typedef enum s_tokens t_tokens;
typedef struct s_elements t_elements;
typedef struct s_cam t_cam;
typedef struct s_ambient t_ambient;
typedef struct s_lighting t_lighting;
typedef struct s_point_light t_point_light;

# include "lighting.h"
# include "ray.h"
# include "hittable.h"
# include "sphere.h"
# include "cylinder.h"
# include "plain.h"
# include "hittable_lst.h"
# include "parser.h"
# include "error.h"

typedef enum s_tokens
{
	A = 1,
	C,
	L,
	SP,
	PL,
	CY
}	t_tokens;

typedef struct s_win
{
	int			h;
	int			w;
	mlx_image_t	*img;
	int			x;
	int			y;
}	t_win;

typedef struct s_cam
{
	float	vfov;
	float	theta;
	float	h;
	float	vp_h;
	float	vp_w;
	float	focal_len;
	t_vec4	orig;
	t_vec4	horiz;
	t_vec4	vert;
	t_vec4	btm_left_cnr;
}	t_cam;

typedef struct s_elements
{
	t_ambient		*ambient;
	t_cam			*cam;
	t_point_light	*light;
	t_hittable_lst	*objs;
}	t_elements;

//element utils
t_elements	elements_init_empty(void);

//utils
float		deg_to_rad(float deg);
float		clamp(float x, float min, float max);
char		*skip_spaces(char *s);
int			ctof(char *s, float *f);

// hit_utils
bool		hit_hittable_list(t_hittable hit, t_hittable_lst *lst);
float		hit_sphere(t_sphere *s, t_ray r);

//color_utils
void		write_color(t_vec4 color, t_win *win);

//vec_utils
float		length_squared(t_vec4 v);
float		length(t_vec4 v);
float		dot(const t_vec4 u, const t_vec4 v);
t_vec4		cross(const t_vec4 u, const t_vec4 v);
t_vec4		unit_vector(t_vec4 v);

#endif // MINIRT_H