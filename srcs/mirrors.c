/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:32:54 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/28 19:34:25 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	pl_mirror(t_elem *elem, t_vec dir, t_plane pl, t_vec rtn)
{
	t_vec		ref;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_vec		rgb;
	t_object	obj;

	obj.type = 0;
	obj.elem = &pl;
	ref = vec_mult_vec(pl.orient, dir);
	ref = vec_mult_vec(ref, pl.orient);
	ref = vec_mult (ref, -2);
	ref = vec_add(dir, ref);
	ref = vec_norm(ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - pl.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn, obj))));
	rgb = vec_mult(rgb, pl.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	sph_mirror(t_elem *elem, t_vec dir, t_sphere sph, t_vec rtn)
{
	t_vec		ref;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_vec		rgb;
	t_object	obj;

	obj.type = 1;
	obj.elem = &sph;
	ref = vec_mult(vec_diff(rtn, sph.pos), vec_dot(dir, vec_diff(rtn, sph.pos)));
	ref = vec_mult (ref, -2);
	ref = vec_add(rtn, ref);
	ref = vec_norm(ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_sph(sph, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - sph.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn, obj))));
	rgb = vec_mult(rgb, sph.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	pl_checkboard(t_elem *elem, t_vec dir, t_plane pl, t_vec rtn)
{
	t_vec		ref;
	t_vec		final;
	t_vec		zero;
	t_vec		dir_zero;
	t_vec		alight;
	t_object	obj;
	t_vec		light;
	t_vec		rgb;
	int			x;
	int			y;
	int			clor;

	dir_zero = vec_diff(pl.orient, dir);
	zero = vec_diff(rtn, pl.pos);
	if ((num_to_pos(pl.orient.x) > num_to_pos(pl.orient.y)
			&& num_to_pos(pl.orient.x) > num_to_pos(pl.orient.z))
		&& (pl.orient.z == 0 || pl.orient.y))
	{
		x = rtn.y / 10;
		y = rtn.z / 10;
	}
	else if ((num_to_pos(pl.orient.y) > num_to_pos(pl.orient.x)
			&& num_to_pos(pl.orient.y) > num_to_pos(pl.orient.z))
		&& (pl.orient.x == 0 || pl.orient.y == 0))
	{
		x = rtn.x / 10;
		y = rtn.z / 10;
	}
	else
	{
		x = rtn.x / 10;
		y = rtn.y / 10;
	}
	if ((rtn.x > 0 && rtn.y > 0) || (rtn.x < 0 && rtn.y < 0))
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
	ref = vec_mult_vec(pl.orient, dir);
	ref = vec_mult_vec(ref, pl.orient);
	ref = vec_mult (ref, -2);
	ref = vec_add(dir, ref);
	ref = vec_norm(ref);
	pl.color = double_to_rgb(clor);
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - pl.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn, obj))));
	rgb = vec_mult(rgb, pl.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}
