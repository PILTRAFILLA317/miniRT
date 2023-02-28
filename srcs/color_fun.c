/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:54:24 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/28 20:24:29 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	cyl_color(t_elem *elem, t_vec dir, t_vec pos, t_cyl cyl)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	rtn = cyl_intersect_point(pos, &cyl, dir);
	alight = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_cyl(cyl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}

int	sph_color(t_elem *elem, t_vec dir, t_vec pos, t_sphere sph)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	rtn = sph_intersect_point(pos, &sph, dir);
	if (sph.x == 1)
		return (sph_mirror(elem, dir, sph, rtn));
	alight = (vec_mult(vec_mult_vec(col_to_01
					(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_sph(sph, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}

int	disc_color(t_elem *elem, t_vec dir, t_vec pos, t_disc disc)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	rtn = disc_intersect_point(pos, &disc, dir);
	light = light_comb_disc(disc, elem, rtn);
	alight = (vec_mult(vec_mult_vec(col_to_01(disc.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}

int	plane_color(t_elem *elem, t_vec dir, t_vec pos, t_plane pl)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	rtn = pl_intersect_point(pos, &pl, dir);
	if (pl.x == 1)
		return (pl_mirror(elem, dir, pl, rtn));
	if (pl.x == 2)
		return (pl_checkboard(elem, dir, pl, rtn));
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}

int	trian_color(t_elem *elem, t_vec dir, t_vec pos, t_tri tri)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	rtn = t_intersect_point(pos, &tri, dir);
	alight = (vec_mult(vec_mult_vec(col_to_01(tri.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_tri(tri, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}
