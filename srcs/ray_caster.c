/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/20 13:53:48 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

double	clamp(double min, double max, double value)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
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
		if (cyl_intersect(elem, c_head, dir))
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

int	color(t_elem *elem, t_vec dir)
{
	t_vec		rtn;
	t_object	obj;
	double		t;

	obj = first_intersect(elem, dir);
	if (obj.elem == NULL)
		return (0);
	if (obj.type == c)
	{
		// return (convert_rgb(((t_cyl *)obj.elem)->color));
		rtn = cyl_intersect_point(elem, obj.elem, dir);
		t = vec_len(vec_diff(elem->cam.pos, rtn));
		t = 1 - clamp(0, 1, t / 150);
		return (convert_rgb(col_to_255(vec_mult_vec(new_vec(t, t, t), col_to_01(((t_cyl *)obj.elem)->color)))));
		
	}
	if (obj.type == s)
	{
		// return (convert_rgb(((t_sphere *)obj.elem)->color));
		rtn = sph_intersect_point(elem, obj.elem, dir);
		t_vec norm;
		norm = vec_norm(points_to_vec(((t_sphere *)obj.elem)->pos, rtn));
		t_vec light;
		light = vec_norm(vec_diff(elem->light->pos, rtn));
		t = vec_dot(norm, light);
		// t = vec_len(vec_diff(elem->cam.pos, rtn));
		// t = 1 - clamp(0, 1, t / 150);
		return (convert_rgb(col_to_255(vec_mult(vec_mult_vec(col_to_01(((t_sphere *)obj.elem)->color),
				col_to_01(elem->light->color)), t * elem->light->bright))));
	}
	if (obj.type == p)
	{
		// return (convert_rgb(((t_plane *)obj.elem)->color));
		rtn = pl_intersect_point(elem, obj.elem, dir);
		t = vec_len(vec_diff(elem->cam.pos, rtn));
		t = 1 - clamp(0, 1, t / 150);
		return (convert_rgb(col_to_255(vec_mult_vec(new_vec(t, t, t), col_to_01(((t_plane *)obj.elem)->color)))));
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
