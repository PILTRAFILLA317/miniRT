/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_getter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:22:37 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 19:25:42 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	id_iterator(t_elem *elem)
{
	t_cyl		*c_head;
	t_plane		*p_head;

	c_head = elem->cyl;
	p_head = elem->pl;
	while (c_head != NULL)
	{
		c_head->id++;
		c_head->bot_disc.id++;
		c_head->top_disc.id++;
		c_head = c_head->next;
	}
	while (p_head != NULL)
	{
		p_head->id++;
		p_head = p_head->next;
	}
}

void	id_creator(t_elem *elem)
{
	int			id;
	t_sphere	*s_head;

	s_head = elem->sphere;
	id = 0;
	while (s_head != NULL)
	{
		s_head->id = id;
		id++;
		s_head = s_head->next;
	}
	id_iterator(elem);
}
