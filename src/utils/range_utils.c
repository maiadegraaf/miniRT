/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   range_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 16:27:07 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/15 16:28:22 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_range	range_init(int min, int max)
{
	t_range	new;

	new.min = min;
	new.max = max;
	return (new);
}
