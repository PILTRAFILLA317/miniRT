/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iw_plane_iter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:08:11 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 13:17:03 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	iw_pl_s_it(t_elem *elem, t_dirpos arg, t_light light)
{
	t_sphere	*s_head;

	s_head = elem->sphere;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
		{
			if (sph_intersect(arg.pos, s_head, arg.dir) == 1)
				if (vec_len(vec_diff(arg.pos,
							sph_intersect_point(arg.pos, s_head, arg.dir)))
					< vec_len(vec_diff(arg.pos, light.pos)))
					return (1);
		}
		s_head = s_head->next;
	}
	return (0);
}

int	iw_pl_c_it(t_elem *elem, t_dirpos arg, t_light light)
{
	t_cyl		*c_head;

	c_head = elem->cyl;
	while (c_head != NULL)
	{
		if (cyl_intersect(arg.pos, c_head, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos,
						cyl_intersect_point(arg.pos, c_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->bot_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos,
							&c_head->bot_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		if (disc_intersect(arg.pos, &c_head->top_disc, arg.dir) == 1)
			if (vec_len(vec_diff(arg.pos, disc_intersect_point(arg.pos,
							&c_head->top_disc, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		c_head = c_head->next;
	}
	return (0);
}

