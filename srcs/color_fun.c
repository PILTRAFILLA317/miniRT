/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:54:24 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 19:32:44 by umartin-         ###   ########.fr       */
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

double	spec_light(t_vec norm, t_vec rtn, t_light *light, t_vec d)
{
	t_vec	ref;
	t_vec	new_vec;
	double	spec;

	ref = vec_norm(vec_diff(d, vec_mult(norm, 2 * vec_dot(d, norm))));
	new_vec = vec_norm(vec_diff(light->pos, rtn));
	spec = vec_dot(ref, new_vec);
	return (pow(fmax(spec, 0.0), 1000) * light->bright);
}

int	sph_color(t_elem *elem, t_dirpos d, t_sphere sph, int *ray)
{
	t_vec		rtn;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_light		*temp;
	t_dirpos	rt;

	temp = elem->light;
	rtn = sph_intersect_point(d.pos, &sph, d.dir);
	rt.dir = d.dir;
	rt.pos = rtn;
	alight = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	if (sph.x == 1 && *ray <= MAX_MIRR_RAYS)
		light = col_to_01(double_to_rgb(sph_mirror(elem, rt, sph, ray)));
	else
	{
		light = light_comb_sph(sph, elem, rtn);
		final = vec_add(alight, light);
	}
	while (temp != NULL)
	{
		final = vec_add(final, vec_mult(temp->color,
					spec_light(points_to_vec(sph.pos, rtn), rtn, temp, d.dir)));
		temp = temp->next;
	}
	return (final = vec_clamp(0, 1, final), convert_rgb(col_to_255(final)));
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
