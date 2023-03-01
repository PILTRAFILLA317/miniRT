/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:32:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/01 17:23:35 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
