/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_linked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:52 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/03 23:29:41 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	plane_checker(t_elem *elem)
{
	if (elem->pl->orient.x < -1 || elem->pl->orient.x > 1)
		return (-1);
	if (elem->pl->orient.y < -1 || elem->pl->orient.y > 1)
		return (-1);
	if (elem->pl->orient.z < -1 || elem->pl->orient.z > 1)
		return (-1);
	if (elem->pl->r < 0 || elem->pl->r > 255)
		return (-1);
	if (elem->pl->g < 0 || elem->pl->g > 255)
		return (-1);
	if (elem->pl->b < 0 || elem->pl->r > 255)
		return (-1);
	return (0);
}

int	plane_pre_chkr(char **fl)
{
	char	**pos;
	char	**dir;
	char	**rgb;

	pos = ft_split(fl[1], ',');
	if (ft_doublestrlen(pos) != 3 || digit_checker(pos[0])
		|| digit_checker(pos[1]) || digit_checker(pos[2]))
		return (error_printer(3), 1);
	dir = ft_split(fl[2], ',');
	if (ft_doublestrlen(dir) != 3 || digit_checker(dir[0])
		|| digit_checker(dir[1]) || digit_checker(dir[2]))
		return (error_printer(3), 1);
	rgb = ft_split(fl[3], ',');
	if (ft_doublestrlen(rgb) != 3 || digit_checker(rgb[0])
		|| digit_checker(rgb[1]) || digit_checker(rgb[2]))
		return (error_printer(3), 1);
	return (0);
}

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
