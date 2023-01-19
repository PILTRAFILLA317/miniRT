/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:55:11 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/19 19:12:09 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

	trgb = 0 << 24 | (int)col.x << 16 | (int)col.y << 8 | (int)col.z;
	return (trgb);
}
