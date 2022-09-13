/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:12:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/13 17:57:31 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	write_color(t_vec4 color, int x, int y, t_win win)
{
	// float	scale;
	int		ir;
	int		ig;
	int		ib;

	// scale = 0.01;

	// color = color * scale;

	// printf("(%f, %f, %f)\n", color[0], color[1], color[2]);

	ir = (int)(255.99 * clamp(color[0], 0, 0.999));
	ig = (int)(255.99 * clamp(color[1], 0, 0.999));
	ib = (int)(255.99 * clamp(color[2], 0, 0.999));

	// printf("(%d, %d, %d)\n", ir, ig, ib);

	mlx_put_pixel(win.img, x, win.h - y - 1, create_rgba(ir, ig, ib, 255));
}

