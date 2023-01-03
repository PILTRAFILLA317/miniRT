/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:07:38 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/03 19:21:28 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cyl	*cyl_creator(char **fl)
{
	char	**pos;
	char	**dir;
	char	**rgb;
	t_cyl	*cyl;

	cyl = malloc(sizeof(t_cyl));
	pos = ft_split(fl[1], ',');
	cyl->pos.x = ft_strtod(pos[0]);
	cyl->pos.y = ft_strtod(pos[1]);
	cyl->pos.z = ft_strtod(pos[2]);
	dir = ft_split(fl[2], ',');
	cyl->orient.x = ft_strtod(dir[0]);
	cyl->orient.y = ft_strtod(dir[1]);
	cyl->orient.z = ft_strtod(dir[2]);
	cyl->diam = ft_strtod(fl[3]);
	cyl->h = ft_strtod(fl[4]);
	rgb = ft_split(fl[5], ',');
	cyl->r = ft_atoi(rgb[0]);
	cyl->g = ft_atoi(rgb[1]);
	cyl->b = ft_atoi(rgb[2]);
	cyl->next = NULL;
	return (cyl);
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
