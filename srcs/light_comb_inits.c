/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_comb_inits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:22:05 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 19:48:52 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light_c	light_comb_pl_init(t_plane pl, t_elem *elem, t_vec rtn)
{
	t_light_c	lc;

	lc.tmp = elem->light;
	lc.t = clamp(0, 1, (1 - (vec_len(points_to_vec(lc.tmp->pos, rtn)))
				/ (lc.tmp->bright * 1000)));
	lc.light = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(lc.tmp->color)), lc.t * lc.tmp->bright));
	lc.arg.dir = vec_norm(vec_diff(lc.tmp->pos, rtn));
	lc.arg.pos = rtn;
	return (lc);
}

t_light_c	light_comb_sph_init(t_sphere sph, t_elem *elem, t_vec rtn)
{
	t_light_c	lc;

	lc.tmp = elem->light;
	lc.t = vec_dot(vec_norm(points_to_vec(sph.pos, rtn)),
			vec_norm(vec_diff(lc.tmp->pos, rtn)));
	lc.t = clamp(0, 1, lc.t);
	lc.t = lc.t * (clamp(0, 1, (1 - (vec_len(points_to_vec(lc.tmp->pos, rtn)))
					/ (lc.tmp->bright * 1000))));
	lc.light = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(lc.tmp->color)), lc.t * lc.tmp->bright));
	lc.arg.dir = vec_norm(vec_diff(lc.tmp->pos, rtn));
	lc.arg.pos = rtn;
	return (lc);
}

t_light_c	light_comb_disc_init(t_disc disc, t_elem *elem, t_vec rtn)
{
	t_light_c	lc;

	lc.tmp = elem->light;
	lc.t = clamp(0, 1, (1 - (vec_len(points_to_vec(lc.tmp->pos, rtn)))
				/ (lc.tmp->bright * 1000)));
	lc.light = (vec_mult(vec_mult_vec(col_to_01(disc.color),
					col_to_01(lc.tmp->color)), lc.t * lc.tmp->bright));
	lc.arg.dir = vec_norm(vec_diff(lc.tmp->pos, rtn));
	lc.arg.pos = rtn;
	return (lc);
}

t_light_c	light_comb_tri_init(t_tri tri, t_elem *elem, t_vec rtn)
{
	t_light_c	lc;

	lc.tmp = elem->light;
	lc.t = vec_dot(vec_norm(tri.orient), vec_norm(vec_diff(lc.tmp->pos, rtn)));
	lc.t = clamp(-1, 1, lc.t);
	lc.t = num_to_pos(lc.t);
	lc.t = lc.t * clamp(0, 1, (1 - (vec_len(points_to_vec(lc.tmp->pos, rtn)))
				/ (lc.tmp->bright * 1000)));
	lc.light = (vec_mult(vec_mult_vec(col_to_01(tri.color),
					col_to_01(lc.tmp->color)), lc.t * lc.tmp->bright));
	lc.arg.dir = vec_norm(vec_diff(lc.tmp->pos, rtn));
	lc.arg.pos = rtn;
	if (i_w_tri(elem, lc.arg, tri, *lc.tmp) == 1)
		lc.light = new_vec(0.0, 0.0, 0.0);
	lc.tmp = lc.tmp->next;
	return (lc);
}

t_light_tc	light_comb_cyl_init(t_cyl cyl, t_elem *elem, t_vec rtn)
{
	t_light_tc	lc;

	lc.tmp = elem->light;
	lc.mid_p = mid_point(cyl, rtn);
	lc.t = vec_dot(vec_norm(points_to_vec(lc.mid_p, rtn)),
			vec_norm(vec_diff(lc.tmp->pos, rtn)));
	lc.t = clamp(0, 1, lc.t);
	lc.t = lc.t * (clamp(0, 1, (1 - (vec_len(points_to_vec(lc.tmp->pos, rtn)))
					/ (lc.tmp->bright * 1000))));
	lc.light = (vec_mult(vec_mult_vec(col_to_01(cyl.color),
					col_to_01(lc.tmp->color)), lc.t * lc.tmp->bright));
	lc.arg.dir = vec_norm(vec_diff(lc.tmp->pos, rtn));
	lc.arg.pos = rtn;
	if (i_w_cyl(elem, lc.arg, cyl, *lc.tmp) == 1)
		lc.light = new_vec(0.0, 0.0, 0.0);
	lc.tmp = lc.tmp->next;
	return (lc);
}
