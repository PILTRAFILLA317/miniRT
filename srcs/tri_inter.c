/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:28:39 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/11 16:33:06 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	t_intersect_point(t_vec pos, t_tri *tri, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(tri->orient, dir);
	p0l0 = points_to_vec(pos, tri->ver[0]);
	t = vec_dot(p0l0, tri->orient) / denom;
	return (vec_point(dir, pos, t));
}

int	tri_intersect(t_vec pos, t_tri *tri, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;
	t_vec	ip;
	t_vec	c;
	t_vec	edge0;
	t_vec	edge1;
	t_vec	edge2;
	t_vec	vp0;
	t_vec	vp1;
	t_vec	vp2;

	denom = vec_dot(tri->orient, dir);
	if (denom != 0)
	{
		p0l0 = points_to_vec(pos, tri->ver[0]);
		t = vec_dot(p0l0, tri->orient) / denom;
		if (t < 0.0)
			return (0);
	}
	ip = t_intersect_point(pos, tri, dir);
	edge0 = vec_diff(tri->ver[1], tri->ver[0]);
	vp0 = vec_diff(ip, tri->ver[0]);
	c = vec_cross(edge0, vp0);
	if (vec_dot(c, tri->orient) < 0)
		return (0);
	edge1 = vec_diff(tri->ver[2], tri->ver[1]);
	vp1 = vec_diff(ip, tri->ver[1]);
	c = vec_cross(edge1, vp1);
	if (vec_dot(c, tri->orient) < 0)
		return (0);
	edge2 = vec_diff(tri->ver[0], tri->ver[2]);
	vp2 = vec_diff(ip, tri->ver[2]);
	c = vec_cross(edge2, vp2);
	if (vec_dot(c, tri->orient) < 0)
		return (0);
	return (1);
}
