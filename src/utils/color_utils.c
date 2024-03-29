/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:12:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/15 18:22:37 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	write_color(t_vec4 color, int x, int y, t_win win)
{
	int	ir;
	int	ig;
	int	ib;

	ir = (int)(255.99 * clamp(color[0], 0, 0.999));
	ig = (int)(255.99 * clamp(color[1], 0, 0.999));
	ib = (int)(255.99 * clamp(color[2], 0, 0.999));
	mlx_put_pixel(win.img, x, win.h - y - 1, create_rgba(ir, ig, ib, 255));
}
