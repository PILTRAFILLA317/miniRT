/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_with.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:17:28 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/27 21:33:17 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	inter_with_sph(t_elem *elem, t_vec dir, t_vec p, t_sphere sph)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(p, s_head, dir) == 1 && s_head->id != sph.id)
			return (1);
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(p, c_head, dir) > 0)
			return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(p, p_head, dir) == 1)
			return (1);
		p_head = p_head->next;
	}
	return (0);
}

int	inter_with_cyl(t_elem *elem, t_vec dir, t_vec p, t_cyl cyl)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(p, s_head, dir) == 1)
			return (1);
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(p, c_head, dir) > 0 && c_head->id != cyl.id)
			return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(p, p_head, dir) == 1)
			return (1);
		p_head = p_head->next;
	}
	return (0);
}

int	inter_with_pl(t_elem *elem, t_vec dir, t_vec p, t_plane pl)
{
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	while (s_head != NULL)
	{
		if (sph_intersect(p, s_head, dir) == 1)
			return (1);
		s_head = s_head->next;
	}
	while (c_head != NULL)
	{
		if (cyl_intersect(p, c_head, dir) > 0)
			return (1);
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		if (pl_intersect(p, p_head, dir) == 1 && p_head->id != pl.id)
			return (1);
		p_head = p_head->next;
	}
	return (0);
}
