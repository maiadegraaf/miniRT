/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable_lst.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 15:41:52 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/13 13:21:25 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_LST_H
# define HITTABLE_LST_H
# include "minirt.h"
# include "hittable.h"

typedef struct s_sphere t_sphere;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;
typedef struct s_hittable t_hittable;

typedef struct s_hittable_lst
{
	t_sphere				*s;
	t_plane					*p;
	t_cylinder				*c;
	t_hittable				*hit;
	t_vec4					color;
	int						i;
	struct s_hittable_lst	*next;
	struct s_hittable_lst	*prev;
}	t_hittable_lst;

//hittable_lst_utils

t_hittable_lst	*ft_hittable_lstnew(t_sphere *s, t_vec4 color);
void			ft_hittable_lstadd_back(t_hittable_lst **lst, t_hittable_lst *new);
void			ft_hittable_lst_rm_first(t_hittable_lst **lst);
void			ft_hittable_lstclear(t_hittable_lst **lst);
t_hittable_lst	*ft_hittable_lstfirst(t_hittable_lst *map);
t_hittable_lst	*ft_hittable_lstlast(t_hittable_lst *map);

#endif // HITTABLE_LST_H