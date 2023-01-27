/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:04:49 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/27 21:29:49 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	light_comb_pl(t_plane pl, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		aux;
	double		t;

	tmp = elem->light;
	t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 300));
	light = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(tmp->color)), t * tmp->bright));
	if (inter_with_pl(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, pl) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 300));
		aux = (vec_mult(vec_mult_vec(col_to_01(pl.color),
				col_to_01(tmp->color)), t * tmp->bright));
		if (inter_with_pl(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, pl) == 1)
			aux = new_vec(0.0, 0.0, 0.0);
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}

t_vec	light_comb_sph(t_sphere sph, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		aux;
	double		t;

	tmp = elem->light;
	t = vec_dot(vec_norm(points_to_vec(sph.pos, rtn)),
			vec_norm(vec_diff(tmp->pos, rtn)));
	t = clamp(0, 1, t);
	t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 500)));
	light = (vec_mult(vec_mult_vec(col_to_01(sph.color),
			col_to_01(tmp->color)), t * tmp->bright));
	if (inter_with_sph(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, sph) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = vec_dot(vec_norm(points_to_vec(sph.pos, rtn)),
			vec_norm(vec_diff(tmp->pos, rtn)));
		t = clamp(0, 1, t);
		t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 500)));
		aux = (vec_mult(vec_mult_vec(col_to_01(sph.color),
			col_to_01(tmp->color)), t * tmp->bright));
		if (inter_with_sph(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, sph) == 1)
			aux = new_vec(0.0, 0.0, 0.0);
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}

t_vec	light_comb_cyl(t_cyl cyl, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		mid_p;
	t_vec		aux;
	double		t;

	tmp = elem->light;
	mid_p = mid_point(cyl, rtn);
	t = vec_dot(vec_norm(points_to_vec(mid_p, rtn)),
			vec_norm(vec_diff(tmp->pos, rtn)));
	t = clamp(0, 1, t);
	t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 500)));
	light = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
					col_to_01(tmp->color)), t * tmp->bright));
	if (inter_with_cyl(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, cyl) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		mid_p = mid_point(cyl, rtn);
		t = vec_dot(vec_norm(points_to_vec(mid_p, rtn)),
				vec_norm(vec_diff(tmp->pos, rtn)));
		t = clamp(0, 1, t);
		t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn))) / 500)));
		aux = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
						col_to_01(tmp->color)), t * tmp->bright));
		if (inter_with_cyl(elem, vec_norm(vec_diff(rtn, tmp->pos)), rtn, cyl) == 1)
			aux = new_vec(0.0, 0.0, 0.0);
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}
