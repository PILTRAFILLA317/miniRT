/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_inter_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:44:01 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:43:36 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

t_vec	sph_intersect_point(t_vec pos, t_sphere *sph, t_vec dir)
{
	t_vec	inter_point;
	t_vec	l;
	float	th[2];
	float	t[2];
	float	d[2];

	l.x = sph->pos.x - pos.x;
	l.y = sph->pos.y - pos.y;
	l.z = sph->pos.z - pos.z;
	d[0] = vec_len(l);
	th[1] = vec_dot(l, dir);
	d[1] = sqrt((d[0] * d[0]) - (th[1] * th[1]));
	th[0] = sqrt(((sph->diam / 2) * (sph->diam / 2)) - (d[1] * d[1]));
	t[0] = th[1] - th[0];
	t[1] = th[1] + th[0];
	inter_point.x = pos.x + (dir.x * t[0]);
	inter_point.y = pos.y + (dir.y * t[0]);
	inter_point.z = pos.z + (dir.z * t[0]);
	return (inter_point);
}

int	sph_intersect(t_vec pos, t_sphere *sph, t_vec dir)
{
	t_vec	l;
	float	ld;
	float	tca;
	float	d;

	l.x = sph->pos.x - pos.x;
	l.y = sph->pos.y - pos.y;
	l.z = sph->pos.z - pos.z;
	ld = vec_len(l);
	tca = vec_dot(l, dir);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (d < (sph->diam / 2))
		return (1);
	return (0);
}
