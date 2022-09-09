/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 16:18:56 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/09 16:15:45 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ctof_dec(char *s, double *d)
{
	float	f;
	float	mul;

	f = 0;
	mul = 1;
	while(ft_isdigit(*s))
	{
		mul /= 10;
		f = f * 10 + (*s - '0');
		s++;
	}
	if (s)
		return (EXIT_FAILURE);
	*d += f * mul;
	return (EXIT_SUCCESS);
}

int	ctof(char *s, float *f)
{
	float	sign;
	double	d;

	sign = 1;
	if (!*s)
		return (EXIT_FAILURE);
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	if (!ft_isdigit(*s) || !ft_strnstr(s, ".", ft_strlen(s)))
		return (EXIT_FAILURE);
	while (ft_isdigit(*s) && (d < FLT_MAX || d > FLT_MIN))
	{
		d = d * 10 + (*s - '0');
		s++;
	}
	if ((*s == '.' && ctof_dec(s, &d)) || s)
		return (EXIT_FAILURE);
	*f = d * sign;
	return (EXIT_SUCCESS);	
}

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

float	clamp(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

char *skip_spaces(char *s)
{
	while (*s && *s == ' ')
		s++;
	return(s);
}