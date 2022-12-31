/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:07:38 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/31 17:10:48 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cyl	*cyl_creator(char **fl)
{
	// char	    **pos;
	// char	    **rgb;
	// t_cyl	*cyl;

	// cyl = malloc(sizeof(t_cyl));
	// pos = ft_split(fl[1], ',');
	// cyl->pos.x = ft_strtod(pos[0]);
	// cyl->pos.y = ft_strtod(pos[1]);
	// cyl->pos.z = ft_strtod(pos[2]);
	// cyl->bright = ft_strtod(fl[2]);
	// rgb = ft_split(fl[3], ',');
	// cyl->r = ft_atoi(rgb[0]);
	// cyl->g = ft_atoi(rgb[1]);
	// cyl->b = ft_atoi(rgb[2]);
	// cyl->next = NULL;
	// return (cyl);
}

void	new_cyl(t_cyl **lst, t_cyl *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
}
