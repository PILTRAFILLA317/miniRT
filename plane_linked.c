/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_linked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:52 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/31 17:10:25 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*plane_creator(char **fl)
{
	// char	**pos;
	// char	**rgb;
	// t_plane	*light;

	// light = malloc(sizeof(t_plane));
	// pos = ft_split(fl[1], ',');
	// light->pos.x = ft_strtod(pos[0]);
	// light->pos.y = ft_strtod(pos[1]);
	// light->pos.z = ft_strtod(pos[2]);
	// light->bright = ft_strtod(fl[2]);
	// rgb = ft_split(fl[3], ',');
	// light->r = ft_atoi(rgb[0]);
	// light->g = ft_atoi(rgb[1]);
	// light->b = ft_atoi(rgb[2]);
	// light->next = NULL;
	// return (light);
}

void	new_plane(t_plane **lst, t_plane *new)
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
