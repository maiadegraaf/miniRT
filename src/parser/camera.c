/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:34:41 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/19 15:08:01 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cam	cam_init(t_vec4 look_from, t_vec4 n, float fov)
{
	t_cam	cam;
	t_vec4	up;
	t_vec4	right;
	float	vp_h;
	float	vp_w;

	up = (t_vec4){0, 1, 0};
	if (n[0] == 0 && n[2] == 0)
		up = (t_vec4){0, 0, 1};
	vp_w = tan(deg_to_rad(fov) / 2);
	vp_h = (vp_w / ASPECT_RATIO);
	right = unit_vector(cross(up, n));
	cam.orig = look_from;
	cam.horiz = right * vp_w;
	cam.vert = vp_h * up;
	cam.btm_left_cnr = cam.orig - cam.horiz / 2
		- cam.vert / 2 + n;
	return (cam);
}

t_cam	*cam_assign(char *line)
{
	t_cam	*new;
	t_vec4	look_from;
	t_vec4	n;
	float	fov;

	new = malloc(sizeof(t_cam));
	line = read_vec4(line, &look_from, 1, 0);
	line = read_vec4(line, &n, -1, 1);
	line = read_float(line, &fov, 0, 180);
	n = unit_vector(n);
	*new = cam_init(look_from, n, fov);
	return (new);
}
