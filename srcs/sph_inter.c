/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:44:01 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/19 20:49:09 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	sph_intersect_point(t_elem *elem, t_sphere *sph, t_vec dir)
{
	t_vec	inter_point;
	t_vec	l;
	float	thc;
	float	t0;
	float	t1;
	float	ld;
	float	tca;
	float	d;

	l.x = sph->pos.x - elem->cam.pos.x;
	l.y = sph->pos.y - elem->cam.pos.y;
	l.z = sph->pos.z - elem->cam.pos.z;
	ld = vec_len(l);
	tca = vec_dot(l, dir);
	d = sqrt((ld * ld) - (tca * tca));
	thc = sqrt(((elem->sphere->diam / 2) * (elem->sphere->diam / 2)) - (d * d));
	t0 = tca - thc;
	t1 = tca + thc;
	inter_point.x = elem->cam.pos.x + (dir.x * t0);
	inter_point.y = elem->cam.pos.y + (dir.y * t0);
	inter_point.z = elem->cam.pos.z + (dir.z * t0);
	return (inter_point);
}

int	sph_intersect(t_elem *elem, t_sphere *sph, t_vec dir)
{
	t_vec	l;
	float	ld;
	float	tca;
	float	d;

	l.x = sph->pos.x - elem->cam.pos.x;
	l.y = sph->pos.y - elem->cam.pos.y;
	l.z = sph->pos.z - elem->cam.pos.z;
	ld = vec_len(l);
	tca = vec_dot(l, dir);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (d < (sph->diam / 2))
		return (1);
	return (0);
}
