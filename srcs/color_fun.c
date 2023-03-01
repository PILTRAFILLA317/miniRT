/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:54:24 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/01 19:10:19 by umartin-         ###   ########.fr       */
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

int	sph_color(t_elem *elem, t_dirpos d, t_sphere sph, int *ray)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_dirpos	rt;

	rtn = sph_intersect_point(d.pos, &sph, d.dir);
	rt.dir = d.dir;
	rt.pos = rtn;
	if (sph.x == 1 && *ray <= MAX_MIRR_RAYS)
		return (sph_mirror(elem, rt, sph, ray));
	alight = (vec_mult(vec_mult_vec(col_to_01
					(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_sph(sph, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	return (convert_rgb(col_to_255(final)));
}

int	plane_color(t_elem *elem, t_dirpos d, t_plane pl, int *ray)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_dirpos	rt;

	rtn = pl_intersect_point(d.pos, &pl, d.dir);
	rt.dir = d.dir;
	rt.pos = rtn;
	if (pl.x == 1 && *ray <= MAX_MIRR_RAYS)
		return (pl_mirror(elem, rt, pl, ray));
	if (pl.x == 2 && *ray <= MAX_MIRR_RAYS)
		return (pl_checkboard(elem, rt, pl, ray));
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
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
