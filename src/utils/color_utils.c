/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 17:12:16 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/08/31 18:16:34 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	write_color(t_vec4 color, int x, int y, t_win win)
{
	int ir = (int)(255.99 * color[0]);
	int ig = (int)(255.99 * color[1]);
	int ib = (int)(255.99 * color[2]);

	mlx_put_pixel(g_img, x, win.h - y - 1, create_rgba(ir, ig, ib, 255));
}