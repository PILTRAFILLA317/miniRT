/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/27 18:48:02 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	num_to_pos(double num)
{
	if (num >= 0)
		return (num);
	else
		return (num * -1);
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
	rtn.x = px + elem->cam.orient.x;
	rtn.y = py + elem->cam.orient.y;
	rtn.z = elem->cam.orient.z;
	rtn = vec_norm (rtn);
	return (rtn);
}

t_object	first_intersect(t_elem *elem, t_vec dir)
{
	double		len;
	t_object	obj;
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	len = 0;
	obj.elem = NULL;
	while (s_head != NULL)
	{
		if (sph_intersect(elem, s_head, dir))
		{
			if (vec_len(vec_diff(elem->cam.pos, sph_intersect_point(elem,
							s_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(elem->cam.pos,
							sph_intersect_point(elem, s_head, dir)));
				obj.elem = s_head;
				obj.type = s;
			}
		}
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(elem, c_head, dir) == 1)
		{
			if (vec_len(vec_diff(elem->cam.pos, cyl_intersect_point(elem,
							c_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(elem->cam.pos,
							cyl_intersect_point(elem, c_head, dir)));
				obj.elem = c_head;
				obj.type = c;
			}
		}
		if (cyl_intersect(elem, c_head, dir) == 2)
		{
			if (vec_len(vec_diff(elem->cam.pos, cyl_intersect_point(elem,
							c_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(elem->cam.pos,
							cyl_intersect_point(elem, c_head, dir)));
				obj.elem = c_head;
				obj.type = d;
			}
		}
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(elem, p_head, dir))
		{
			if (vec_len(vec_diff(elem->cam.pos, pl_intersect_point(elem,
							p_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(elem->cam.pos,
							pl_intersect_point(elem, p_head, dir)));
				obj.elem = p_head;
				obj.type = p;
			}
		}
		p_head = p_head->next;
	}
	return (obj);
}

t_vec	mid_point(t_cyl cyl, t_vec inter)
{
	t_vec	rtn;
	t_vec	l;
	float	tca;

	l = vec_diff(inter, cyl.pos);
	tca = vec_dot(l, cyl.orient);
	rtn = vec_point(cyl.orient, cyl.pos, tca);
	return (rtn);
}

int	color(t_elem *elem, t_vec dir)
{
	t_vec		rtn;
	t_object	obj;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	obj = first_intersect(elem, dir);
	if (obj.elem == NULL)
		return (0);
	if (obj.type == c)
	{
		rtn = cyl_intersect_point(elem, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_cyl *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_cyl(* (t_cyl *)obj.elem, elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(light)));
	}
	if (obj.type == d)
	{
		rtn = cyl_intersect_point(elem, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_cyl *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_cyl(* (t_cyl *)obj.elem, elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(light)));
	}
	if (obj.type == s)
	{
		rtn = sph_intersect_point(elem, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_sphere *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_sph(* ((t_sphere *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == p)
	{
		rtn = pl_intersect_point(elem, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_plane *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_pl(* ((t_plane *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
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
