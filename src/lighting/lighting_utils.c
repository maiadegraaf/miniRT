/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 14:20:28 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/14 16:06:32 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_point_light	point_light_init(t_vec4 position, t_vec4 color, float power)
{
	t_point_light	node;

	node.position = position;
	node.diff_color = color;
	node.diff_power = power;
	node.spec_color = (t_vec4){1, 1, 1, 1};
	node.spec_power = 2;
	return (node);
}
