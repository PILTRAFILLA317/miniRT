/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_comb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:04:49 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/10 23:12:19 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	light_comb_pl(t_plane pl, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		aux;
	t_dirpos	arg;
	double		t;

	tmp = elem->light;
	t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
				/ (tmp->bright * 1000)));
	light = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(tmp->color)), t * tmp->bright));
	arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
	arg.pos = rtn;
	if (inter_with_pl(elem, arg, pl, *tmp) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
					/ (tmp->bright * 1000)));
		aux = (vec_mult(vec_mult_vec(col_to_01(pl.color),
						col_to_01(tmp->color)), t * tmp->bright));
		arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
		arg.pos = rtn;
		if (inter_with_pl(elem, arg, pl, *tmp) == 1)
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
	t_dirpos	arg;
	double		t;

	tmp = elem->light;
	t = vec_dot(vec_norm(points_to_vec(sph.pos, rtn)),
			vec_norm(vec_diff(tmp->pos, rtn)));
	t = clamp(0, 1, t);
	t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
					/ (tmp->bright * 1000))));
	light = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(tmp->color)), t * tmp->bright));
	arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
	arg.pos = rtn;
	if (inter_with_sph(elem, arg, sph, *tmp) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = vec_dot(vec_norm(points_to_vec(sph.pos, rtn)),
				vec_norm(vec_diff(tmp->pos, rtn)));
		t = clamp(0, 1, t);
		t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
						/ (tmp->bright * 1000))));
		aux = (vec_mult(vec_mult_vec(col_to_01(sph.color),
						col_to_01(tmp->color)), t * tmp->bright));
		arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
		arg.pos = rtn;
		if (inter_with_sph(elem, arg, sph, *tmp) == 1)
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
	t_dirpos	arg;
	double		t;

	tmp = elem->light;
	mid_p = mid_point(cyl, rtn);
	t = vec_dot(vec_norm(points_to_vec(mid_p, rtn)),
			vec_norm(vec_diff(tmp->pos, rtn)));
	t = clamp(0, 1, t);
	t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
					/ (tmp->bright * 1000))));
	light = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
					col_to_01(tmp->color)), t * tmp->bright));
	arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
	arg.pos = rtn;
	if (inter_with_cyl(elem, arg, cyl, *tmp) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		mid_p = mid_point(cyl, rtn);
		t = vec_dot(vec_norm(points_to_vec(mid_p, rtn)),
				vec_norm(vec_diff(tmp->pos, rtn)));
		t = clamp(0, 1, t);
		t = t * (clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
						/ (tmp->bright * 1000))));
		aux = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
						col_to_01(tmp->color)), t * tmp->bright));
		arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
		arg.pos = rtn;
		if (inter_with_cyl(elem, arg, cyl, *tmp) == 1)
			aux = new_vec(0.0, 0.0, 0.0);
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}

t_vec	light_comb_disc(t_disc disc, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		aux;
	t_dirpos	arg;
	double		t;

	tmp = elem->light;
	t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
				/ (tmp->bright * 1000)));
	light = (vec_mult(vec_mult_vec(col_to_01(disc.color),
					col_to_01(tmp->color)), t * tmp->bright));
	arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
	arg.pos = rtn;
	if (inter_with_disc(elem, arg, disc, *tmp) == 1)
		light = new_vec(0.0, 0.0, 0.0);
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
					/ (tmp->bright * 1000)));
		aux = (vec_mult(vec_mult_vec(col_to_01(disc.color),
						col_to_01(tmp->color)), t * tmp->bright));
		arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
		arg.pos = rtn;
		if (inter_with_disc(elem, arg, disc, *tmp) == 1)
			aux = new_vec(0.0, 0.0, 0.0);
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}

t_vec	light_comb_tri(t_tri tri, t_elem *elem, t_vec rtn)
{
	t_light		*tmp;
	t_vec		light;
	t_vec		aux;
	t_dirpos	arg;
	double		t;

	tmp = elem->light;
	t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
				/ (tmp->bright * 1000)));
	light = (vec_mult(vec_mult_vec(col_to_01(tri.color),
					col_to_01(tmp->color)), t * tmp->bright));
	arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
	arg.pos = rtn;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		t = clamp(0, 1, (1 - (vec_len(points_to_vec(tmp->pos, rtn)))
					/ (tmp->bright * 1000)));
		aux = (vec_mult(vec_mult_vec(col_to_01(tri.color),
						col_to_01(tmp->color)), t * tmp->bright));
		arg.dir = vec_norm(vec_diff(tmp->pos, rtn));
		arg.pos = rtn;
		light = vec_add(aux, light);
		light = vec_clamp(0, 1, light);
		tmp = tmp->next;
	}
	return (light);
}