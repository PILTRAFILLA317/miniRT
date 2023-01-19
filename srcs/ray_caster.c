/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/19 20:07:15 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	cyl_intersect_point(t_elem *elem, t_cyl *cyl, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	t_vec	x;

	x = vec_diff(elem->cam.pos, cyl->pos);
	a = vec_dot(dir, dir) - (vec_dot(dir, cyl->orient) * vec_dot(dir, cyl->orient));
	b = (vec_dot(dir, x) - vec_dot(dir, cyl->orient) * vec_dot(x, cyl->orient)) * 2;
	c = vec_dot(x, x) - (vec_dot(x, cyl->orient) * vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		return (vec_point(dir, elem->cam.pos, t1));
	}
	if (disc_intersect(elem, &cyl->bot_disc, dir) == 1 || disc_intersect(elem, &cyl->top_disc, dir) == 1)
	{
		if (vec_len(disc_intersect_point(elem, &cyl->bot_disc, dir))
			> vec_len(disc_intersect_point(elem, &cyl->top_disc, dir)))
			return (disc_intersect_point(elem, &cyl->top_disc, dir), dir);
		else
			return (disc_intersect_point(elem, &cyl->bot_disc, dir), dir);
	}
	return (cyl->pos);
}

int	cyl_intersect(t_elem *elem, t_cyl *cyl, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	t1;
	t_vec	p;
	t_vec	x;

	x = vec_diff(elem->cam.pos, cyl->pos);
	a = vec_dot(dir, dir) - (vec_dot(dir, cyl->orient) * vec_dot(dir, cyl->orient));
	b = (vec_dot(dir, x) - vec_dot(dir, cyl->orient) * vec_dot(x, cyl->orient)) * 2;
	c = vec_dot(x, x) - (vec_dot(x, cyl->orient) * vec_dot(x, cyl->orient)) - ((cyl->diam / 2) * (cyl->diam / 2));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t1 = (-b - sqrt(d)) / (2 * a);
		if (t1 > 0)
		{
			p = vec_point(dir, elem->cam.pos, t1);
			double angle1 = vec_dot(vec_norm(points_to_vec(cyl->pos, p)), cyl->orient);
			double angle2 = vec_dot(vec_norm(points_to_vec(cyl->pos2, p)), cyl->orient2);
			if (angle1 >= 0 && angle2 >= 0)
				return (1);
		}
	}
	if (disc_intersect(elem, &cyl->bot_disc, dir) == 1 || disc_intersect(elem, &cyl->top_disc, dir) == 1)
		return (1);
	return (0);
}

t_vec	disc_intersect_point(t_elem *elem, t_disc *disc, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;
	t_vec	ip;

	denom = vec_dot(disc->orient, dir);
	p0l0 = points_to_vec(elem->cam.pos, disc->pos);
	t = vec_dot(p0l0, disc->orient) / denom;
	ip = vec_point(dir, elem->cam.pos, t);
	return (ip);
}

int	disc_intersect(t_elem *elem, t_disc *disc, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;
	t_vec	ip;

	denom = vec_dot(disc->orient, dir);
	if (denom != 0)
	{
		p0l0 = points_to_vec(elem->cam.pos, disc->pos);
		t = vec_dot(p0l0, disc->orient) / denom;
		if (t > 0.0)
		{
			ip = vec_point(dir, elem->cam.pos, t);
			if (vec_len(points_to_vec(ip, disc->pos)) < (disc->diam / 2.0))
				return (1);
		}
	}
	return (0);
}

t_vec	pl_intersect_point(t_elem *elem, t_plane *pl, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(pl->orient, dir);
	p0l0 = vec_diff(elem->cam.pos, pl->pos);
	t = vec_dot(p0l0, pl->orient) / denom;
	return (vec_point(dir, elem->cam.pos, t));
}

int	pl_intersect(t_elem *elem, t_plane *pl, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(pl->orient, dir);
	if (denom != 0)
	{
		p0l0 = vec_diff(elem->cam.pos, pl->pos);
		t = vec_dot(p0l0, pl->orient) / denom;
		if (t > 0.0)
			return (1);
	}
	return (0);
}

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

t_vec	vec_rotation(int x, int y, t_elem *elem)
{
	t_vec	rtn;
	double	imageaspectratio;
	double	px;
	double	py;
	double	scale;

	scale = tan((elem->cam.fov * 0.5) * (M_PI / 180));
	imageaspectratio = WIN_X / WIN_Y;
	px = (2.0 * ((x + 0.5) / WIN_X) - 1.0) * imageaspectratio * scale;
	py = (1.0 - 2.0 * ((y + 0.5) / WIN_Y)) * scale;
	rtn.x = px - elem->cam.orient.x;
	rtn.y = py - elem->cam.orient.y;
	rtn.z = elem->cam.orient.z;
	rtn = vec_norm (rtn);
	return (rtn);
}

double	clamp(double min, double max, double value)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

int		color(t_elem *elem, t_vec dir)
{
	t_vec	rtn;
	double	t;

	if (cyl_intersect(elem, elem->cyl, dir))
	{
		return(0xFFFFFF);
		rtn = cyl_intersect_point(elem, elem->cyl, dir);
		t = vec_len(vec_diff(elem->cam.pos, rtn));
		t = 1 - clamp(0, 1, t / 150);
		return (convert_rgb(col_to_255(new_vec(t, t, t))));
	}
	return (0);
}

void	ray_caster(t_elem *elem)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_X)
	{
		y = 0;
		while (y <= WIN_Y)
		{
			// if (pl_intersect(elem, elem->pl, vec_rotation(x, y, elem)) == 1)
			// 	mlx_pixel_put(elem->mlx, elem->win, x, y, 0xFFFFFF);
			mlx_pixel_put(elem->mlx, elem->win, x, y, color(elem, vec_rotation(x, y, elem)));
			y++;
		}
		x++;
	}
}
