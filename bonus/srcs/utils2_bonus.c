/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:28:02 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:44:11 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

double	num_to_pos(double num)
{
	if (num >= 0)
		return (num);
	else
		return (num * -1);
}

t_vec	mid_point(t_cyl cyl, t_vec inter)
{
	t_vec	rtn;
	t_vec	l;
	float	tca;

	l = vec_diff(inter, cyl.pos);
	tca = vec_dot(l, cyl.orient);
	rtn = vec_point(cyl.orient, cyl.pos, tca);
	return (rtn);
}
