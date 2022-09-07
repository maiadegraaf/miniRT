/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_lst.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:41:52 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/07 13:24:06 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LST_H
# define HITTABLE_LST_H
# include "minirt.h"
# include "hittable.h"

typedef struct s_sphere t_sphere;
typedef struct s_hittable t_hittable;

typedef struct s_hittable_lst
{
	t_sphere				*s;
	t_hittable				*hit;
	t_vec4					color;
	struct s_hittable_lst	*next;
	struct s_hittable_lst	*prev;
}	t_hittable_lst;

//hittable_lst_utils

t_hittable_lst	*ft_hittable_lstnew(t_sphere *s, t_vec4 color);
void			ft_hittable_lstadd_back(t_hittable_lst **lst, t_hittable_lst *new);
void			ft_hittable_lst_rm_first(t_hittable_lst **lst);
void			ft_hittable_lstclear(t_hittable_lst **lst);

#endif // HITTABLE_LST_H