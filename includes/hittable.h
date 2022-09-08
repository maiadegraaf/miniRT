/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hittable.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 13:59:45 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/09/08 11:58:53 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITTABLE_H
# define HITTABLE_H
# include "minirt.h"
# include "ray.h"

typedef struct s_ray t_ray;

typedef struct s_hit_record
{
	t_vec4	p;
	t_vec4	n;
	float	t;
	float	root2;
	bool	front_face;
} t_hit_record;

typedef struct s_hittable
{
	t_ray			*r;
	float			t_min;
	float			t_max;
	t_hit_record	*rec;
} t_hittable;

//hittable utils
t_hittable	hittable_init(t_ray *r, float t_min, float t_max, t_hit_record *rec);

//hit_record utils
void			set_face_normal(t_hit_record *rec, const t_ray r, const t_vec4 outward_normal);
t_hit_record	*hit_rec_init_empty(void);

#endif // HITTABLE_H