/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:11 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:41:04 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

t_vec	col_to_01(t_vec	col)
{
	return (vec_div(col, 255));
}

t_vec	col_to_255(t_vec	col)
{
	return (vec_mult(col, 255));
}

int	convert_rgb(t_vec col)
{
	int	trgb;

	if (col.x > 255)
		col.x = 0;
	if (col.y > 255)
		col.y = 0;
	if (col.z > 255)
		col.z = 0;
	trgb = 0 << 24 | (int)col.x << 16 | (int)col.y << 8 | (int)col.z;
	return (trgb);
}

t_vec	double_to_rgb(int num)
{
	t_vec	rtn;

	rtn.x = (num & 0x00ff0000) >> 16;
	rtn.y = (num & 0x0000ff00) >> 8;
	rtn.z = (num & 0x000000ff);
	return (rtn);
}
