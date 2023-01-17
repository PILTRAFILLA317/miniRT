/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/17 21:15:33 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	pl_intersect(t_elem *elem, t_vec dir)
{
	double	t;
	double	denom;
	t_vec	p0l0;

	denom = vec_dot(elem->pl->orient, dir);
	if (denom > 1e-6)
	{
		p0l0 = points_to_vec(elem->cam.pos, elem->pl->pos);
		t = vec_dot(p0l0, elem->pl->orient) / denom;
		if (t > 0.0)
			return (1);
	}
	return (0);
}

t_vec	sph_intersect_point(t_elem *elem, t_vec dir, double d, double tca)
{
	t_vec	inter_point;
	float	thc;
	float	t0;
	float	t1;

	thc = sqrt(((elem->sphere->diam / 2) * (elem->sphere->diam / 2)) - (d * d));
	t0 = tca - thc;
	t1 = tca + thc;
	inter_point.x = elem->cam.pos.x + (dir.x * t0);
	inter_point.y = elem->cam.pos.y + (dir.y * t0);
	inter_point.z = elem->cam.pos.z + (dir.z * t0);
	return (inter_point);
}

int	sph_intersect(t_elem *elem, t_vec dir)
{
	t_vec	l;
	float	ld;
	float	tca;
	float	d;

	l.x = elem->sphere->pos.x - elem->cam.pos.x;
	l.y = elem->sphere->pos.y - elem->cam.pos.y;
	l.z = elem->sphere->pos.z - elem->cam.pos.z;
	ld = vec_len(l);
	tca = vec_dot(l, dir);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (d < (elem->sphere->diam / 2))
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
	rtn.x = px;
	rtn.y = py;
	rtn.z = -1;
	rtn = vec_norm (rtn);
	return (rtn);
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
			if (sph_intersect(elem, vec_rotation(x, y, elem)) == 1)
				mlx_pixel_put(elem->mlx, elem->win, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}
