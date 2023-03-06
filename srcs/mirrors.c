/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:32:54 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 15:21:25 by becastro         ###   ########.fr       */
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
	t_vec		ref;
	t_vec		final;
	t_vec		zero;
	t_vec		dir_zero;
	t_vec		alight;
	t_dirpos	rf;
	t_object	obj;
	t_vec		light;
	t_vec		rgb;
	int			x;
	int			y;
	int			clor;

	dir_zero = vec_diff(pl.orient, rt.dir);
	zero = vec_diff(rt.pos, pl.pos);
	if ((num_to_pos(pl.orient.x) > num_to_pos(pl.orient.y)
			&& num_to_pos(pl.orient.x) > num_to_pos(pl.orient.z))
		&& (pl.orient.z == 0 || pl.orient.y))
	{
		x = rt.pos.y / 10;
		y = rt.pos.z / 10;
	}
	else if ((num_to_pos(pl.orient.y) > num_to_pos(pl.orient.x)
			&& num_to_pos(pl.orient.y) > num_to_pos(pl.orient.z))
		&& (pl.orient.x == 0 || pl.orient.y == 0))
	{
		x = rt.pos.x / 10;
		y = rt.pos.z / 10;
	}
	else
	{
		x = rt.pos.x / 10;
		y = rt.pos.y / 10;
	}
	if ((rt.pos.x > 0 && rt.pos.y > 0) || (rt.pos.x < 0 && rt.pos.y < 0))
	{
		if ((x % 2 != 0) && (y % 2 != 0))
			clor = 0xFFFFFF;
		if ((x % 2 == 0) && (y % 2 != 0))
			clor = 0x000000;
		if ((x % 2 != 0) && (y % 2 == 0))
			clor = 0x000000;
		if ((x % 2 == 0) && (y % 2 == 0))
			clor = 0xFFFFFF;
	}
	else
	{
		if ((x % 2 != 0) && (y % 2 != 0))
			clor = 0x000000;
		if ((x % 2 == 0) && (y % 2 != 0))
			clor = 0xFFFFFF;
		if ((x % 2 != 0) && (y % 2 == 0))
			clor = 0xFFFFFF;
		if ((x % 2 == 0) && (y % 2 == 0))
			clor = 0x000000;
	}
	obj.type = 0;
	obj.elem = &pl;
	ref = vec_mult_vec(pl.orient, rt.dir);
	ref = vec_mult_vec(ref, pl.orient);
	ref = vec_mult (ref, -2);
	ref = vec_add(rt.dir, ref);
	ref = vec_norm(ref);
	pl.color = double_to_rgb(clor);
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rt.pos);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - pl.ref));
	rf.dir = ref;
	rf.pos = rt.pos;
	(*ray)++;
	rgb = col_to_01(double_to_rgb((color(elem, rf, obj, ray))));
	rgb = vec_mult(rgb, pl.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}
