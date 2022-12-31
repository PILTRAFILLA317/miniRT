/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_linked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:19:49 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/31 14:26:34 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	light_checker(t_elem *elem)
{
	if (elem->light->bright < 0 || elem->light->bright > 1)
		return (-1);
	if (elem->light->r < 0 || elem->light->r > 255)
		return (-1);
	if (elem->light->g < 0 || elem->light->g > 255)
		return (-1);
	if (elem->light->b < 0 || elem->light->r > 255)
		return (-1);
	return (0);
}

t_light	*light_creator(char **fl)
{
	char	**pos;
	char	**rgb;
	t_light	*light;

	light = malloc(sizeof(t_light));
	pos = ft_split(fl[1], ',');
	light->pos.x = ft_strtod(pos[0]);
	light->pos.y = ft_strtod(pos[1]);
	light->pos.z = ft_strtod(pos[2]);
	light->bright = ft_strtod(fl[2]);
	rgb = ft_split(fl[3], ',');
	light->r = ft_atoi(rgb[0]);
	light->g = ft_atoi(rgb[1]);
	light->b = ft_atoi(rgb[2]);
	light->next = NULL;
	return (light);
}

void	new_light(t_light **lst, t_light *new)
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
