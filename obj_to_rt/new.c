/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:28:58 by becastro          #+#    #+#             */
/*   Updated: 2023/03/07 16:31:15 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

int	new_trian(t_ver **trian, t_ver *new)
{
	t_ver	*tmp;

	if (!(*trian))
	{
		*trian = new;
		return (0);
	}
	tmp = *trian;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	new_face(t_tri **trian, t_tri *new)
{
	t_tri	*tmp;

	if (!(*trian))
	{
		*trian = new;
		return (0);
	}
	tmp = *trian;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	new_norm(t_norm **norm, t_norm *new)
{
	t_norm	*tmp;

	if (!(*norm))
	{
		*norm = new;
		return (0);
	}
	tmp = *norm;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
