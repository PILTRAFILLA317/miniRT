/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iw_cyl_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:08:11 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 13:03:39 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	iw_cyl_s_it(t_elem *elem, t_dirpos arg, t_light light)
{
	t_sphere	*s_head;

	s_head = elem->sphere;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos,
						sph_intersect_point(arg.pos, s_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		s_head = s_head->next;
	}
	return (0);
}


static int	cyl_c_checker(t_cyl *c_head,
	t_dirpos arg, t_cyl cyl, t_light light)
{
	if (cyl_intersect(arg.pos, c_head, arg.dir) == 1
		&& c_head->id != cyl.id)
		if (vec_len(vec_diff(arg.pos,
					cyl_intersect_point(arg.pos, c_head, arg.dir)))
			< vec_len(vec_diff(arg.pos, light.pos)))
			return (1);
	return (0);
}

int	iw_cyl_c_it(t_elem *elem, t_dirpos arg, t_cyl cyl, t_light light)
{
	t_cyl		*c_head;

	c_head = elem->cyl;
	while (c_head != NULL)
	{
		if (cyl_c_checker(c_head, arg, cyl, light))
			return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1
			&& c_head->id != cyl.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos,
							&c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1
			&& c_head->id != cyl.id)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos,
							&c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	return (0);
}


int	iw_cyl_p_it(t_elem *elem, t_dirpos arg, t_light light)
{
	t_plane		*p_head;

	p_head = elem->pl;
	while (p_head != NULL)
	{
		if (pl_intersect(arg.pos, p_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos,
						pl_intersect_point(arg.pos, p_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		p_head = p_head->next;
	}
	return (0);
}

int	iw_cyl_t_it(t_elem *elem, t_dirpos arg, t_light light)
{
	t_tri		*t_head;

	t_head = elem->t;
	while (t_head != NULL)
	{
		if (tri_intersect(arg.pos, t_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos,
						t_intersect_point(arg.pos, t_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		t_head = t_head->next;
	}
	return (0);
}
