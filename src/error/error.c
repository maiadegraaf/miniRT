/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maiadegraaf <maiadegraaf@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 13:11:40 by maiadegraaf   #+#    #+#                 */
/*   Updated: 2022/09/12 09:53:41 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	ft_error(int i)
{
	ft_printf("Error\n");
	if (i == 0)
		ft_printf("Incorrect file type\n");
	if (i == 1)
		ft_printf("Empty file\n");
	if (i > 20)
	{
		if (i == 21)
			ft_printf("Ambient light ");
		else if (i == 22)
			ft_printf("A camera ");
		else if (i == 23)
			ft_printf("A light ");
		ft_printf("can only be declared once in the scene.\n");
	}
	if (i == 2)
		ft_printf(" is not an existing element.\n");
	if (i == 3)
		ft_printf("Out of range.\n");
	if (i == 4)
		ft_printf("Incomplete line\n");
	if (i == 10)
		ft_printf("MALLOC ERROR\n");
	if (i == 20)
		ft_printf("No input\n");
	exit(EXIT_FAILURE);
}
