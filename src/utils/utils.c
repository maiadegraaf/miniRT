/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 11:29:50 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/26 16:14:23 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	write_color(t_vec3 *color, t_mlx_win *win, int samples_per_pixel)
{
	double	r;
	double	g;
	double	b;
	double	scale;

	scale = 1.0 / samples_per_pixel;
	// printf("x = %f, y = %f, z = %f\n", color->x, color->y, color->z);
	r = color->x * scale;
	g = color->y * scale;
	b = color->z * scale;
	// printf("r = %f, g = %f, b = %f\n", r, g, b);
	mlx_put_pixel(g_img, win->x, win->height - win->y - 1,
		create_rgba(
			(int)(256 * clamp(r, 0.0, 0.99)),
			(int)(256 * clamp(g, 0.0, 0.99)),
			(int)(256 * clamp(b, 0.0, 0.99)), 255));
}

double	deg_to_rad(double deg)
{
	return ((deg * M_PI) / 180.0);
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
