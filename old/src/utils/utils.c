/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 11:29:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/05/03 17:47:03 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	write_color(t_vec4 color, t_mlx_win *win, int samples_per_pixel)
{
	float	r;
	float	g;
	float	b;
	// printf("x = %f, y = %f, z = %f\n", color->x, color->y, color->z);
	r = color[0] / samples_per_pixel;
	g = color[1] / samples_per_pixel;
	b = color[2] / samples_per_pixel;
	// printf("r = %f, g = %f, b = %f\n", r, g, b);
	mlx_put_pixel(g_img, win->x, win->height - win->y - 1,
		create_rgba(
			(int)(256 * clamp(r, 0.0, 0.99)),
			(int)(256 * clamp(g, 0.0, 0.99)),
			(int)(256 * clamp(b, 0.0, 0.99)), 255));
}

float	deg_to_rad(float deg)
{
	return ((deg * M_PI) / 180.0);
}

float	clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
