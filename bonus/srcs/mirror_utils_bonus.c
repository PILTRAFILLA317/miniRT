/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:54:12 by becastro          #+#    #+#             */
/*   Updated: 2023/03/08 17:43:06 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

void	pl_checkboard_axis_calc(int *axis, t_plane pl, t_dirpos rt)
{
	if ((num_to_pos(pl.orient.x) > num_to_pos(pl.orient.y)
			&& num_to_pos(pl.orient.x) > num_to_pos(pl.orient.z))
		&& (pl.orient.z == 0 || pl.orient.y))
	{
		axis[0] = rt.pos.y / 10;
		axis[1] = rt.pos.z / 10;
	}
	else if ((num_to_pos(pl.orient.y) > num_to_pos(pl.orient.x)
			&& num_to_pos(pl.orient.y) > num_to_pos(pl.orient.z))
		&& (pl.orient.x == 0 || pl.orient.y == 0))
	{
		axis[0] = rt.pos.x / 10;
		axis[1] = rt.pos.z / 10;
	}
	else
	{
		axis[0] = rt.pos.x / 10;
		axis[1] = rt.pos.y / 10;
	}
}

int	pl_checkboard_color_calc(int *axis, t_dirpos rt)
{
	int	clor;

	if ((rt.pos.x > 0 && rt.pos.y > 0) || (rt.pos.x < 0 && rt.pos.y < 0))
	{
		if ((axis[0] % 2 != 0) && (axis[1] % 2 != 0))
			clor = 0xFFFFFF;
		if ((axis[0] % 2 == 0) && (axis[1] % 2 != 0))
			clor = 0x000000;
		if ((axis[0] % 2 != 0) && (axis[1] % 2 == 0))
			clor = 0x000000;
		if ((axis[0] % 2 == 0) && (axis[1] % 2 == 0))
			clor = 0xFFFFFF;
	}
	else
	{
		if ((axis[0] % 2 != 0) && (axis[1] % 2 != 0))
			clor = 0x000000;
		if ((axis[0] % 2 == 0) && (axis[1] % 2 != 0))
			clor = 0xFFFFFF;
		if ((axis[0] % 2 != 0) && (axis[1] % 2 == 0))
			clor = 0xFFFFFF;
		if ((axis[0] % 2 == 0) && (axis[1] % 2 == 0))
			clor = 0x000000;
	}
	return (clor);
}

void	pl_cb_vec_init(t_vec *vec, t_plane *pl, t_dirpos rt, int clor)
{
	vec[0] = vec_mult_vec(pl->orient, rt.dir);
	vec[0] = vec_mult_vec(vec[0], pl->orient);
	vec[0] = vec_mult (vec[0], -2);
	vec[0] = vec_add(rt.dir, vec[0]);
	vec[0] = vec_norm(vec[0]);
	pl->color = double_to_rgb(clor);
}

void	pl_cb_vec_calc(t_vec *vec, t_plane pl, t_dirpos rt, t_elem *elem)
{
	vec[4] = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	vec[5] = light_comb_pl(pl, elem, rt.pos);
	vec[1] = vec_add(vec[4], vec[5]);
	vec[1] = vec_clamp(0, 1, vec[1]);
	vec[1] = vec_mult(vec[1], (1 - pl.ref));
}
