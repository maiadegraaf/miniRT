/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 16:12:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/02 09:57:56 by maiadegraaf   ########   odam.nl         */
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
# define WIDTH 800

typedef struct s_ray t_ray;
typedef float t_vec4 __attribute__ ((vector_size (16)));

# include "ray.h"

mlx_image_t	*g_img;


typedef struct s_win
{
	int h;
	int w;
}	t_win;

typedef struct s_cam
{
	float vp_h;
	float vp_w;
	float focal_len;
	t_vec4 orig;
	t_vec4 horiz;
	t_vec4 vert;
	t_vec4 btm_left_cnr;
} t_cam;

float hit_sphere(const t_vec4 center, float radius, t_ray r);

//color_utils
void	write_color(t_vec4 color, int x, int y, t_win win);

//vec_utils
float	length_squared(t_vec4 v);
float	length(t_vec4 v);
float dot(const t_vec4 u, const t_vec4 v);
t_vec4 cross(const t_vec4 u, const t_vec4 v);
t_vec4 unit_vector(t_vec4 v);

#endif // MINIRT_H