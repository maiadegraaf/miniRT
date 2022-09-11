/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:41 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/09 16:50:37 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cam cam_init(t_vec4 look_from, t_vec4 look_at, t_vec4 vup, float vfov)
{
	t_cam	n;
	t_vec4	w;
	t_vec4	u;
	t_vec4	v;

	n.vfov = vfov;
	n.theta = deg_to_rad(n.vfov);
	n.h = tan((float)n.theta/2);
	n.vp_h = (float)(2.0 * n.h);
	n.vp_w = ASPECT_RATIO * n.vp_h;
	n.focal_len = 1.0;
	w = unit_vector(look_from - look_at);
	u = unit_vector(cross(vup, w));
	v = cross(w, u);
	n.orig = look_from;
	n.horiz = n.vp_w * u;
	n.vert = n.vp_h * v;
	n.btm_left_cnr = n.orig - n.horiz/2 - n.vert/2 - w;
	return (n);
}

t_cam	*cam_assign(char *line)
{
	t_cam	*new = NULL;
	(void) line;
	return (new);
}