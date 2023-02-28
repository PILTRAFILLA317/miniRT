/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_w.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:17:28 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/20 17:38:21 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	i_w_sph(t_elem *elem, t_dirpos arg, t_sphere sph, t_light light)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	t_head = elem->t;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1 && s_head->id != sph.id)
			if (vec_len(vec_diff(arg.pos, sph_intersect_point(arg.pos, s_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}

int	i_w_cyl(t_elem *elem, t_dirpos arg, t_cyl cyl, t_light light)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	t_head = elem->t;
	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, sph_intersect_point(arg.pos, s_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1 && c_head->id != cyl.id)
			if (vec_len(vec_diff(arg.pos, cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1 && c_head->id != cyl.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1 && c_head->id != cyl.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}

int	i_w_pl(t_elem *elem, t_dirpos arg, t_plane pl, t_light light)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	t_head = elem->t;
	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
		{
			if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
				if (vec_len(vec_diff(arg.pos, sph_intersect_point(arg.pos, s_head, arg.dir)))
					< vec_len(vec_diff(arg.pos, light.pos)))
					return (1);
		}
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1 && p_head->id != pl.id)
			if (vec_len(vec_diff(arg.pos, pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}

int	i_w_disc(t_elem *elem, t_dirpos arg, t_disc disc, t_light light)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	t_head = elem->t;
	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
		{
			if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
				if (vec_len(vec_diff(arg.pos, sph_intersect_point(arg.pos, s_head, arg.dir)))
					< vec_len(vec_diff(arg.pos, light.pos)))
					return (1);
		}
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1 && c_head->id != disc.id)
			if (vec_len(vec_diff(arg.pos, cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1 && c_head->id != disc.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1 && c_head->id != disc.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}

int	i_w_tri(t_elem *elem, t_dirpos arg, t_tri tri, t_light light)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;
	t_tri		*t_head;

	t_head = elem->t;
	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
		{
			if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
				if (vec_len(vec_diff(arg.pos, sph_intersect_point(arg.pos, s_head, arg.dir)))
					< vec_len(vec_diff(arg.pos, light.pos)))
					return (1);
		}
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos, &c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1 && t_head->id != tri.id)
			if (vec_len(vec_diff(arg.pos, t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}
