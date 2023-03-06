/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iw_sph_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:08:11 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 12:17:56 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	iw_sph_s_it(t_elem *elem, t_dirpos arg, t_sphere sph, t_light light)
{
	t_sphere	*s_head;

	s_head = elem->sphere;
	while (s_head != NULL)
	{
		if (sph_intersect(arg.pos, s_head, arg.dir) == 1
			&& s_head->id != sph.id)
			if (vec_len(vec_diff(arg.pos,
						sph_intersect_point(arg.pos, s_head, arg.dir)))
				< vec_len(vec_diff(arg.pos, light.pos)))
				return (1);
		s_head = s_head->next;
	}
	return (0);
}
