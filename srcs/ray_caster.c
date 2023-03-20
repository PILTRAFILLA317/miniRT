/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/20 15:42:28 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	vec_rotation(double x, double y, t_elem *elem)
{
	t_vec	rtn;
	t_vec	right;
	t_vec	up;

	right = vec_mult(elem->cam.right, x * elem->cam.w);
	up = vec_mult(elem->cam.up, y * elem->cam.h);
	rtn = vec_add(vec_add(right, up), elem->cam.orient);
	rtn = vec_norm (rtn);
	return (rtn);
}

t_object	first_intersect(t_elem *elem, t_vec dir, t_vec pos, t_object co)
{
	t_objlen	ol;
	t_dirpos	dp;

	dp.dir = dir;
	dp.pos = pos;
	ol.len = 0;
	ol.obj.elem = NULL;
	ol = cyl_f_i(elem, dp, ol);
	ol = pl_f_i(elem, dp, co, ol);
	ol = sph_f_i(elem, dp, co, ol);
	ol = tri_f_i(elem, dp, ol);
	return (ol.obj);
}

int	color(t_elem *elem, t_dirpos dp, t_object co, int *ray)
{
	t_object	obj;

	obj = first_intersect(elem, dp.dir, dp.pos, co);
	if (obj.elem == NULL)
		return (0);
	if (obj.type == c)
		return (cyl_color(elem, dp.dir, dp.pos, (*(t_cyl *)obj.elem)));
	if (obj.type == d)
		return (disc_color(elem, dp.dir, dp.pos, (*(t_disc *)obj.elem)));
	if (obj.type == s)
		return (sph_color(elem, dp, (*(t_sphere *)obj.elem), ray));
	if (obj.type == p)
		return (plane_color(elem, dp, (*(t_plane *)obj.elem), ray));
	if (obj.type == t)
		return (trian_color(elem, dp.dir, dp.pos, (*(t_tri *)obj.elem)));
	return (0);
}

void	ray_caster(t_elem *elem)
{
	double		s[2];
	int			i[3];
	int			*r;
	t_dirpos	d;
	t_object	obj;

	obj.type = n;
	r = malloc(sizeof(int) * (WIN_X + 1) * (WIN_Y + 1) + 1);
	i[2] = -1;
	i[0] = 0;
	while (++i[2] <= WIN_Y)
	{
		i[1] = -1;
		while (++i[1] <= WIN_X)
		{
			s[0] = (double)i[1] * 2 / WIN_X - 1;
			s[1] = 1 - (double)i[2] * 2 / WIN_Y;
			d.pos = elem->cam.pos;
			d.dir = vec_rotation(s[0], s[1], elem);
			r[i[0]] = 0;
			mlx_pixel_put(elem->mlx, elem->win, i[1], i[2],
				color(elem, d, obj, &r[i[0]]));
			i[0]++;
		}
	}
}
