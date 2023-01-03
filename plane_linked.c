/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_linked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:52 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/03 19:33:13 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*plane_creator(char **fl)
{
	char	**pos;
	char	**dir;
	char	**rgb;
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	pos = ft_split(fl[1], ',');
	plane->pos.x = ft_strtod(pos[0]);
	plane->pos.y = ft_strtod(pos[1]);
	plane->pos.z = ft_strtod(pos[2]);
	dir = ft_split(fl[2], ',');
	plane->orient.x = ft_strtod(dir[0]);
	plane->orient.y = ft_strtod(dir[1]);
	plane->orient.z = ft_strtod(dir[2]);
	rgb = ft_split(fl[3], ',');
	plane->r = ft_atoi(rgb[0]);
	plane->g = ft_atoi(rgb[1]);
	plane->b = ft_atoi(rgb[2]);
	plane->next = NULL;
	return (plane);
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
