/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_comb_inits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:22:05 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 17:01:44 by becastro         ###   ########.fr       */
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
