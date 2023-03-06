/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:44:22 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 11:59:09 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	cyl_intersect_point(t_vec pos, t_cyl *cyl, t_vec dir)
{
	double	i[4];
	double	t1;
	t_vec	x;

	x = vec_diff(pos, cyl->pos);
	i[0] = vec_dot(dir, dir) - (vec_dot(dir, cyl->orient)
			* vec_dot(dir, cyl->orient));
	i[1] = (vec_dot(dir, x) - vec_dot(dir, cyl->orient)
			* vec_dot(x, cyl->orient)) * 2;
	i[2] = vec_dot(x, x) - (vec_dot(x, cyl->orient)
			* vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	i[3] = i[1] * i[1] - 4 * i[0] * i[2];
	if (i[3] >= 0)
	{
		t1 = (-i[1] - sqrt(i[3])) / (2 * i[0]);
		return (vec_point(dir, pos, t1));
	}
	return (cyl->pos);
}

void	cyl_init(double *i, t_vec *pos, t_cyl *cyl, t_vec *dir)
{
	t_vec	x;

	x = vec_diff(*pos, cyl->pos);
	i[0] = vec_dot(*dir, *dir) - (vec_dot(*dir, cyl->orient)
			* vec_dot(*dir, cyl->orient));
	i[1] = (vec_dot(*dir, x) - vec_dot(*dir, cyl->orient)
			* vec_dot(x, cyl->orient)) * 2;
	i[2] = vec_dot(x, x) - (vec_dot(x, cyl->orient)
			* vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	i[3] = i[1] * i[1] - 4 * i[0] * i[2];
}

int	cyl_intersect(t_vec pos, t_cyl *cyl, t_vec dir)
{
	double	i[4];
	double	t1;
	t_vec	p;
	double	a[2];

	cyl_init(i, &pos, cyl, &dir);
	if (i[3] >= 0)
	{
		t1 = (-i[1] - sqrt(i[3])) / (2 * i[0]);
		if (t1 > 0)
		{
			p = vec_point(dir, pos, t1);
			a[0] = vec_dot(vec_norm(points_to_vec(cyl->pos, p)), cyl->orient);
			a[1] = vec_dot(vec_norm(points_to_vec(cyl->pos2, p)), cyl->orient2);
			if (a[0] >= 0 && a[1] >= 0)
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
