/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_inter_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:44:11 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/20 14:57:44 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

t_vec	pl_intersect_point(t_vec pos, t_plane *pl, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(pl->orient, dir);
	p0l0 = points_to_vec(pos, pl->pos);
	t = vec_dot(p0l0, pl->orient) / denom;
	return (vec_point(dir, pos, t));
}

int	pl_intersect(t_vec pos, t_plane *pl, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(pl->orient, dir);
	if (denom != 0)
	{
		p0l0 = points_to_vec(pos, pl->pos);
		t = vec_dot(p0l0, pl->orient) / denom;
		if (t > 0.0)
			return (1);
	}
	return (0);
}
