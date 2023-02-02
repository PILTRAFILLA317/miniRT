/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/02 17:39:42 by umartin-         ###   ########.fr       */
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

t_object	first_intersect(t_elem *elem, t_vec dir, t_vec pos)
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
		if (cyl_intersect(pos, c_head, dir) == 2)
		{
			if (vec_len(vec_diff(pos, cyl_intersect_point(pos,
							c_head, dir))) < len || len == 0)
			{
				len = vec_len(vec_diff(pos,
							cyl_intersect_point(pos, c_head, dir)));
				obj.elem = c_head;
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
	t_vec	ref;
	t_vec	alight;
	t_vec	light;
	t_vec	final;
	t_vec	rgb;

	ref = vec_mult(vec_diff(rtn, sph.pos), vec_dot(dir, vec_diff(rtn, sph.pos)));
	ref = vec_mult (ref, -2);
	ref = vec_add(rtn, ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(sph.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_sph(sph, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - sph.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn))));
	rgb = vec_mult(rgb, sph.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	pl_mirror(t_elem *elem, t_vec dir, t_plane pl, t_vec rtn)
{
	t_vec	ref;
	t_vec	alight;
	t_vec	light;
	t_vec	final;
	t_vec	rgb;

	ref = vec_norm(vec_mult(pl.orient, vec_dot(dir, pl.orient)));
	ref = vec_mult (ref, -2);
	ref = vec_add(rtn, ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - pl.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn))));
	rgb = vec_mult(rgb, pl.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	color(t_elem *elem, t_vec dir, t_vec pos)
{
	t_vec		rtn;
	t_object	obj;
	t_vec		alight;
	t_vec		light;
	t_vec		final;

	obj = first_intersect(elem, dir, pos);
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
		printf("TOP DISC = ");
		vec_printer(((t_cyl *)obj.elem)->pos2);
		printf("BOT DISC = ");
		vec_printer(((t_cyl *)obj.elem)->pos);
		printf("\n");
		if (cyl_intersect(pos, obj.elem, dir) == 3)
		{
			return (0xFFFFFF);
			rtn = disc_intersect_point(pos, &((t_cyl *)obj.elem)->top_disc, dir);
			light = light_comb_disc((*(t_cyl *)obj.elem).top_disc, elem, rtn);
			alight = (vec_mult(vec_mult_vec(col_to_01(((t_cyl *)obj.elem)->top_disc.color),
							col_to_01(elem->alight.color)), elem->alight.ratio));
		}
		else
		{
			rtn = disc_intersect_point(pos, &((t_cyl *)obj.elem)->bot_disc, dir);
			light = light_comb_disc((*(t_cyl *)obj.elem).bot_disc, elem, rtn);
			alight = (vec_mult(vec_mult_vec(col_to_01(((t_cyl *)obj.elem)->bot_disc.color),
							col_to_01(elem->alight.color)), elem->alight.ratio));
		}
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
		if (((t_plane *)obj.elem)->x == 1)
			return (pl_mirror(elem, dir, (*(t_plane *)obj.elem), rtn));
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_plane *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_pl(*((t_plane *)obj.elem), elem, rtn);
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
			mlx_pixel_put(elem->mlx, elem->win, x, y,
				color(elem, vec_rotation(x, y, elem), elem->cam.pos));
			y++;
		}
		x++;
	}
}
