/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:56:53 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 18:56:55 by becastro         ###   ########.fr       */
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

static int	intersect_checker(t_vec *vec, t_tri *tri)
{
	if (vec_dot(vec[2], tri->orient) < 0)
		return (0);
	vec[4] = vec_diff(tri->ver[2], tri->ver[1]);
	vec[7] = vec_diff(vec[1], tri->ver[1]);
	vec[2] = vec_cross(vec[4], vec[7]);
	if (vec_dot(vec[2], tri->orient) < 0)
		return (0);
	return (1);
}

int	tri_intersect(t_vec pos, t_tri *tri, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	vec[9];

	denom = vec_dot(tri->orient, dir);
	if (denom != 0)
	{
		vec[0] = points_to_vec(pos, tri->ver[0]);
		t = vec_dot(vec[0], tri->orient) / denom;
		if (t < 0.0)
			return (0);
	}
	vec[1] = t_intersect_point(pos, tri, dir);
	vec[3] = vec_diff(tri->ver[1], tri->ver[0]);
	vec[6] = vec_diff(vec[1], tri->ver[0]);
	vec[2] = vec_cross(vec[3], vec[6]);
	if (!intersect_checker(vec, tri))
		return (0);
	vec[5] = vec_diff(tri->ver[0], tri->ver[2]);
	vec[8] = vec_diff(vec[1], tri->ver[2]);
	vec[2] = vec_cross(vec[5], vec[8]);
	if (vec_dot(vec[2], tri->orient) < 0)
		return (0);
	return (1);
}
