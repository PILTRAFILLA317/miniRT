/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/20 21:17:13 by umartin-         ###   ########.fr       */
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

		if (o.type == 0)
		{
			if (p_head->id == ((t_plane *)o.elem)->id)
			{
				p_head = p_head->next;
				continue ;
			}
		}
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

int	pl_mirror(t_elem *elem, t_vec dir, t_plane pl, t_vec rtn)
{
	t_vec		ref;
	t_vec		alight;
	t_vec		light;
	t_vec		final;
	t_vec		rgb;
	t_object	obj;

	obj.type = 0;
	obj.elem = &pl;
	ref = vec_mult_vec(pl.orient, dir);
	ref = vec_mult_vec(ref, pl.orient);
	ref = vec_mult (ref, -2);
	ref = vec_add(dir, ref);
	ref = vec_norm(ref);
	alight = (vec_mult(vec_mult_vec(col_to_01(pl.color),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
	final = vec_mult(final, (1 - pl.ref));
	rgb = col_to_01(double_to_rgb((color(elem, ref, rtn, obj))));
	rgb = vec_mult(rgb, pl.ref);
	final = vec_add(final, rgb);
	return (convert_rgb(col_to_255(final)));
}

int	pl_checkboard(t_elem *elem, t_vec dir, t_plane pl, t_vec rtn)
{
	t_vec		final;
	t_vec		zero;
	t_vec		dir_zero;
	t_vec		alight;
	t_vec		light;
	int			x;
	int			y;
	int			color;

	dir_zero = vec_diff(pl.orient, dir);
	zero = vec_diff(rtn, pl.pos);
	x = rtn.x / 5;
	y = rtn.y / 5;
	if ((rtn.x > 0 && rtn.y > 0) || (rtn.x < 0 && rtn.y < 0))
	{
		if ((x % 2 != 0) && (y % 2 != 0))
			color = 0xFFFFFF;
		if ((x % 2 == 0) && (y % 2 != 0))
			color = 0x000000;
		if ((x % 2 != 0) && (y % 2 == 0))
			color = 0x000000;
		if ((x % 2 == 0) && (y % 2 == 0))
			color = 0xFFFFFF;
	}
	else
	{
		if ((x % 2 != 0) && (y % 2 != 0))
			color = 0x000000;
		if ((x % 2 == 0) && (y % 2 != 0))
			color = 0xFFFFFF;
		if ((x % 2 != 0) && (y % 2 == 0))
			color = 0xFFFFFF;
		if ((x % 2 == 0) && (y % 2 == 0))
			color = 0x000000;
	}
	alight = (vec_mult(vec_mult_vec(col_to_01(double_to_rgb(color)),
					col_to_01(elem->alight.color)), elem->alight.ratio));
	light = light_comb_pl(pl, elem, rtn);
	final = vec_add(alight, light);
	final = vec_clamp(0, 1, final);
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
		if (((t_plane *)obj.elem)->x == 1)
			return (pl_mirror(elem, dir, (*(t_plane *)obj.elem), rtn));
		if (((t_plane *)obj.elem)->x == 2)
			return (pl_checkboard(elem, dir, (*(t_plane *)obj.elem), rtn));
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_plane *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_pl(*((t_plane *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	if (obj.type == t)
	{
		rtn = t_intersect_point(pos, obj.elem, dir);
		alight = (vec_mult(vec_mult_vec(col_to_01(((t_tri *)obj.elem)->color),
						col_to_01(elem->alight.color)), elem->alight.ratio));
		light = light_comb_tri(*((t_tri *)obj.elem), elem, rtn);
		final = vec_add(alight, light);
		final = vec_clamp(0, 1, final);
		return (convert_rgb(col_to_255(final)));
	}
	return (0);
}

void	*thread_routine(void *data)
{
	t_th		th;
	int			end;
	int			y;
	int			x;
	int			clr;
	double		xx;
	double		yy;
	t_object	obj;

	th = *(t_th *)data;
	obj.type = 4;
	end = (WIN_Y / NUM_THREAD * th.core) + (WIN_Y / NUM_THREAD);
	y = WIN_Y / NUM_THREAD * th.core;
	while (y <= end)
	{
		x = 0;
		while (x <= WIN_X)
		{
			xx = (double)x * 2 / WIN_X - 1;
			yy = 1 - (double)y * 2 / WIN_Y;
			clr = color(th.elem, vec_rotation(xx, yy, th.elem), th.elem->cam.pos, obj);
			pthread_mutex_lock(&th.elem->pixl);
			mlx_pixel_put(th.elem->mlx, th.elem->win, x, y, clr);
			pthread_mutex_unlock(&th.elem->pixl);
			x++;
		}
		y++;
	}
	return (NULL);
}

void	ray_caster(t_elem *elem)
{
	int	i;

	i = -1;
	elem->th = (t_th *)malloc(sizeof(t_th) * NUM_THREAD);
	pthread_mutex_init(&elem->pixl, 0);
	while (++i < NUM_THREAD)
	{
		elem->th[i].elem = elem;
		elem->th[i].core = i;
		if (pthread_create(&elem->th[i].th, NULL, thread_routine,
				&elem->th[i]) != 0)
			printf("WUAAAAAA");
	}
	i = -1;
	while (++i < NUM_THREAD)
		if (pthread_join(elem->th[i].th, NULL))
			printf("WUAAAAAA");
}
