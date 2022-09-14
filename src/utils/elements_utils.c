/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   elements_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:15:42 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/14 14:52:42 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_elements	elements_init_empty(void)
{
	t_elements	new;

	new.ambient = NULL;
	new.cam = NULL;
	new.light = NULL;
	new.objs = NULL;
	return (new);
}
