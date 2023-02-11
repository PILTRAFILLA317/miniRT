/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/11 14:57:43 by umartin-         ###   ########.fr       */
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

t_object	first_intersect(t_elem *elem, t_vec dir, t_vec pos, t_object o)
{
	double		len;
	t_object	obj;
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	t_head = elem->t;
	len = 0;
	obj.elem = NULL;
	while (c_head != NULL)
	{
		if (cyl_intersect(pos, c_head, dir) == 1)
		{
			if (vec_len(vec_diff(pos, cyl_intersect_point(pos,
							c_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							cyl_intersect_point(pos, c_head, dir)));
				obj.elem = c_head;
				obj.type = c;
			}
		}
		if (disc_intersect(pos, &c_head->bot_disc, dir) == 1)
		{
			if (vec_len(vec_diff(pos, disc_intersect_point(pos,
							&c_head->bot_disc, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							disc_intersect_point(pos, &c_head->bot_disc, dir)));
				obj.elem = &c_head->bot_disc;
				obj.type = d;
			}
		}
		if (disc_intersect(pos, &c_head->top_disc, dir) == 1)
		{
			if (vec_len(vec_diff(pos, disc_intersect_point(pos,
							&c_head->top_disc, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							disc_intersect_point(pos, &c_head->top_disc, dir)));
				obj.elem = &c_head->top_disc;
				obj.type = d;
			}
		}
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(pos, p_head, dir))
		{
			if (vec_len(vec_diff(pos, pl_intersect_point(pos,
							p_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							pl_intersect_point(pos, p_head, dir)));
				obj.elem = p_head;
				obj.type = p;
			}
		}
		p_head = p_head->next;
	}
	while (s_head != NULL)
	{
		if (o.type == 1)
		{
			if (s_head->id == ((t_sphere *)o.elem)->id)
			{
				s_head = s_head->next;
				continue ;
			}
		}
		if (sph_intersect(pos, s_head, dir))
		{
			if (vec_len(vec_diff(pos, sph_intersect_point(pos,
							s_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							sph_intersect_point(pos, s_head, dir)));
				obj.elem = s_head;
				obj.type = s;
			}
		}
		s_head = s_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(pos, t_head, dir))
		{
			if (vec_len(vec_diff(pos, t_intersect_point(pos,
							t_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							t_intersect_point(pos, t_head, dir)));
				obj.elem = t_head;
				obj.type = t;
			}
		}
		t_head = t_head->next;
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

int	sph_mirror(t_elem *elem, t_vec dir, t_sphere sph, t_vec rtn)
{
	t_vec		ref;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_vec		rgb;
	t_object	obj;

	obj.type = 1;
	obj.elem = &sph;
	ref = vec_mult(vec_diff(rtn, sph.pos), vec_dot(dir, vec_diff(rtn, sph.pos)));
	ref = vec_mult (ref, -2);
	ref = vec_add(rtn, ref);
	ref = vec_norm(ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_sph(sph, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - sph.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn, obj))));
	rgb = vec_mult(rgb, sph.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	color(t_elem *elem, t_vec dir, t_vec pos, t_object o)
{
	t_vec		rtn;
	t_object	obj;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	obj = first_intersect(elem, dir, pos, o);
	if (obj.elem == NULL)
		return (0);
	if (obj.type == c)
	{
		rtn = cyl_intersect_point(pos, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_cyl *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_cyl(*(t_cyl *)obj.elem, elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == d)
	{
		rtn = disc_intersect_point(pos, obj.elem, dir);
		light = light_comb_disc(*(t_disc *)obj.elem, elem, rtn);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_disc *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == s)
	{
		rtn = sph_intersect_point(pos, obj.elem, dir);
		if (((t_sphere *)obj.elem)->x == 1)
			return (sph_mirror(elem, dir, (*(t_sphere *)obj.elem), rtn));
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_sphere *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_sph(*((t_sphere *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == p)
	{
		rtn = pl_intersect_point(pos, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_plane *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_pl(*((t_plane *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == t)
	{
		return (0xFFFFFF);
		// rtn = t_intersect_point(pos, obj.elem, dir);
		// alight = (vec_mult(vec_mult_vec(col_to_01(((t_tri *)obj.elem)->color),
		// 				col_to_01(elem->alight.color)), elem->alight.ratio));
		// light = light_comb_tri(*((t_tri *)obj.elem), elem, rtn);
		// final = vec_add(alight, light);
		// final = vec_clamp(0, 1, final);
		// return (convert_rgb(col_to_255(final)));
	}
	return (0);
}

void	ray_caster(t_elem *elem)
{
	int			x;
	int			y;
	t_object	obj;

	x = 0;
	obj.type = 4;
	while (x <= WIN_X)
	{
		y = 0;
		while (y <= WIN_Y)
		{
			mlx_pixel_put(elem->mlx, elem->win, x, y,
				color(elem, vec_rotation(x, y, elem), elem->cam.pos, obj));
			y++;
		}
		x++;
	}
}
