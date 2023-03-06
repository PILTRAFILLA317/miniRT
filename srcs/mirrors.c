/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:32:54 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 15:54:08 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	pl_mirror(t_elem *elem, t_dirpos rt, t_plane pl, int *ray)
{
	t_vec		vec[5];
	t_dirpos	rf;
	t_object	obj;

	obj.type = 0;
	obj.elem = &pl;
	vec[0] = vec_mult_vec(pl.orient, rt.dir);
	vec[0] = vec_mult_vec(vec[0], pl.orient);
	vec[0] = vec_mult (vec[0], -2);
	vec[0] = vec_add(rt.dir, vec[0]);
	vec[0] = vec_norm(vec[0]);
	vec[1] = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	vec[2] = light_comb_pl(pl, elem, rt.pos);
	vec[3] = vec_add(vec[1], vec[2]);
	vec[3] = vec_clamp(0, 1, vec[3]);
	vec[3] = vec_mult(vec[3], (1 - pl.ref));
	rf.dir = vec[0];
	rf.pos = rt.pos;
	(*ray)++;
	vec[4] = col_to_01(double_to_rgb((color(elem, rf, obj, ray))));
	vec[4] = vec_mult(vec[4], pl.ref);
	vec[3] = vec_add(vec[3], vec[4]);
	return (convert_rgb(col_to_255(vec[3])));
}

int	sph_mirror(t_elem *elem, t_dirpos rt, t_sphere sph, int *ray)
{
	t_vec		vec[5];
	t_dirpos	rf;
	t_object	obj;

	obj.type = 1;
	obj.elem = &sph;
	vec[0] = vec_mult(vec_diff(rt.pos, sph.pos),
			vec_dot(rt.dir, vec_diff(rt.pos, sph.pos)));
	vec[0] = vec_mult (vec[0], -2);
	vec[0] = vec_add(rt.pos, vec[0]);
	vec[0] = vec_norm(vec[0]);
	vec[1] = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	vec[2] = light_comb_sph(sph, elem, rt.pos);
	vec[3] = vec_add(vec[1], vec[2]);
	vec[3] = vec_clamp(0, 1, vec[3]);
	vec[3] = vec_mult(vec[3], (1 - sph.ref));
	rf.dir = vec[0];
	rf.pos = rt.pos;
	(*ray)++;
	vec[4] = col_to_01(double_to_rgb((color(elem, rf, obj, ray))));
	vec[4] = vec_mult(vec[4], sph.ref);
	vec[3] = vec_add(vec[3], vec[4]);
	return (convert_rgb(col_to_255(vec[3])));
}



int	pl_checkboard(t_elem *elem, t_dirpos rt, t_plane pl, int *ray)
{
	t_vec		vec[7];
	t_dirpos	rf;
	t_object	obj;
	int			axis[2];
	int			clor;

	vec[3] = vec_diff(pl.orient, rt.dir);
	vec[2] = vec_diff(rt.pos, pl.pos);
	pl_checkboard_axis_calc(axis, pl, rt);
	clor = pl_checkboard_color_calc(axis, rt);
	obj.type = 0;
	obj.elem = &pl;
	pl_cb_vec_init(vec, pl, rt, clor);
	pl_cb_vec_calc(vec, pl, rt, elem);
	rf.dir = vec[0];
	rf.pos = rt.pos;
	(*ray)++;
	vec[6] = col_to_01(double_to_rgb((color(elem, rf, obj, ray))));
	vec[6] = vec_mult(vec[6], pl.ref);
	vec[1] = vec_add(vec[1], vec[6]);
	return (convert_rgb(col_to_255(vec[1])));
}
