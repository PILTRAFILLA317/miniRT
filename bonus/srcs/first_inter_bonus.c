/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_inter_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:32:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/20 16:53:39 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

t_objlen	pl_f_i(t_elem *elem, t_dirpos d, t_object co, t_objlen ol)
{
	t_plane		*p_head;
	t_objlen	rtn;

	p_head = elem->pl;
	rtn = ol;
	while (p_head != NULL)
	{
		if ((co.type != 0) || (p_head->id != ((t_plane *)co.elem)->id))
		{
			if (pl_intersect(d.pos, p_head, d.dir))
			{
				if (vec_len(vec_diff(d.pos, pl_intersect_point(d.pos,
								p_head, d.dir))) < rtn.len || rtn.len == 0)
				{
					rtn.len = vec_len(vec_diff(d.pos,
								pl_intersect_point(d.pos, p_head, d.dir)));
					rtn.obj.elem = p_head;
					rtn.obj.type = p;
				}
			}
		}
		p_head = p_head->next;
	}
	return (rtn);
}

t_objlen	sph_f_i(t_elem *elem, t_dirpos d, t_object co, t_objlen ol)
{
	t_sphere	*s_head;
	t_objlen	rtn;

	s_head = elem->sphere;
	rtn = ol;
	while (s_head != NULL)
	{
		if ((co.type != 1) || (s_head->id != ((t_sphere *)co.elem)->id))
		{
			if (sph_intersect(d.pos, s_head, d.dir))
			{
				if (vec_len(vec_diff(d.pos, sph_intersect_point(d.pos,
								s_head, d.dir))) < rtn.len || rtn.len == 0)
				{
					rtn.len = vec_len(vec_diff(d.pos,
								sph_intersect_point(d.pos, s_head, d.dir)));
					rtn.obj.elem = s_head;
					rtn.obj.type = s;
				}
			}
		}
		s_head = s_head->next;
	}
	return (rtn);
}

t_objlen	tri_f_i(t_elem *elem, t_dirpos d, t_objlen ol)
{
	t_tri		*t_head;
	t_objlen	rtn;

	t_head = elem->t;
	rtn = ol;
	while (t_head != NULL)
	{
		if (tri_intersect(d.pos, t_head, d.dir))
		{
			if (vec_len(vec_diff(d.pos, t_intersect_point(d.pos,
							t_head, d.dir))) < rtn.len || rtn.len == 0)
			{
				rtn.len = vec_len(vec_diff(d.pos,
							t_intersect_point(d.pos, t_head, d.dir)));
				rtn.obj.elem = t_head;
				rtn.obj.type = t;
			}
		}
		t_head = t_head->next;
	}
	return (rtn);
}

t_objlen	disc_f_i_ut(t_dirpos dd, t_objlen ol, t_disc disc)
{
	t_objlen	rtn;

	rtn = ol;
	if (disc_intersect(dd.pos, &disc, dd.dir))
	{
		if (vec_len(vec_diff(dd.pos, disc_intersect_point(dd.pos,
						&disc, dd.dir))) < rtn.len || rtn.len == 0)
		{
			rtn.len = vec_len(vec_diff(dd.pos,
						disc_intersect_point(dd.pos, &disc, dd.dir)));
			rtn.obj.elem = &disc;
			rtn.obj.type = d;
		}
	}
	return (rtn);
}

t_objlen	cyl_f_i(t_elem *elem, t_dirpos d, t_objlen ol)
{
	t_cyl		*c_head;
	t_objlen	rtn;

	c_head = elem->cyl;
	rtn = ol;
	while (c_head != NULL)
	{
		if (cyl_intersect(d.pos, c_head, d.dir) == 1)
		{
			if (vec_len(vec_diff(d.pos, cyl_intersect_point(d.pos,
							c_head, d.dir))) < rtn.len || rtn.len == 0)
			{
				rtn.len = vec_len(vec_diff(d.pos,
							cyl_intersect_point(d.pos, c_head, d.dir)));
				rtn.obj.elem = c_head;
				rtn.obj.type = c;
			}
		}
		rtn = disc_f_i_ut(d, rtn, c_head->bot_disc);
		rtn = disc_f_i_ut(d, rtn, c_head->top_disc);
		c_head = c_head->next;
	}
	return (rtn);
}
