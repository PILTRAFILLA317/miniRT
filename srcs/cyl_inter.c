/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:44:22 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/20 18:21:37 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	cyl_intersect_point(t_vec pos, t_cyl *cyl, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	t_vec	x;

	x = vec_diff(pos, cyl->pos);
	a = vec_dot(dir, dir) - (vec_dot(dir, cyl->orient)
			* vec_dot(dir, cyl->orient));
	b = (vec_dot(dir, x) - vec_dot(dir, cyl->orient)
			* vec_dot(x, cyl->orient)) * 2;
	c = vec_dot(x, x) - (vec_dot(x, cyl->orient)
			* vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		return (vec_point(dir, pos, t1));
	}
	return (cyl->pos);
}

int	cyl_intersect(t_vec pos, t_cyl *cyl, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	t_vec	p;
	t_vec	x;
	double	a1;
	double	a2;

	x = vec_diff(pos, cyl->pos);
	a = vec_dot(dir, dir) - (vec_dot(dir, cyl->orient)
			* vec_dot(dir, cyl->orient));
	b = (vec_dot(dir, x) - vec_dot(dir, cyl->orient)
			* vec_dot(x, cyl->orient)) * 2;
	c = vec_dot(x, x) - (vec_dot(x, cyl->orient)
			* vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		if (t1 > 0)
		{
			p = vec_point(dir, pos, t1);
			a1 = vec_dot(vec_norm(points_to_vec(cyl->pos, p)), cyl->orient);
			a2 = vec_dot(vec_norm(points_to_vec(cyl->pos2, p)), cyl->orient2);
			if (a1 >= 0 && a2 >= 0)
				return (1);
		}
	}
	return (0);
}

t_vec	disc_intersect_point(t_vec pos, t_disc *disc, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;
	t_vec	ip;

	denom = vec_dot(disc->orient, dir);
	p0l0 = points_to_vec(pos, disc->pos);
	t = vec_dot(p0l0, disc->orient) / denom;
	ip = vec_point(dir, pos, t);
	return (ip);
}

int	disc_intersect(t_vec pos, t_disc *disc, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;
	t_vec	ip;

	denom = vec_dot(disc->orient, dir);
	if (denom != 0)
	{
		p0l0 = points_to_vec(pos, disc->pos);
		t = vec_dot(p0l0, disc->orient) / denom;
		if (t > 0.0)
		{
			ip = vec_point(dir, pos, t);
			if (vec_len(points_to_vec(ip, disc->pos)) < (disc->diam / 2.0))
				return (1);
		}
	}
	return (0);
}
