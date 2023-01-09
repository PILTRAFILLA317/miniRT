/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:07:38 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/09 16:27:22 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	cyl_checker(t_elem *elem)
{
	if (elem->cyl->orient.x < -1 || elem->cyl->orient.x > 1)
		return (-1);
	if (elem->cyl->orient.y < -1 || elem->cyl->orient.y > 1)
		return (-1);
	if (elem->cyl->orient.z < -1 || elem->cyl->orient.z > 1)
		return (-1);
	if (elem->cyl->r < 0 || elem->cyl->r > 255)
		return (-1);
	if (elem->cyl->g < 0 || elem->cyl->g > 255)
		return (-1);
	if (elem->cyl->b < 0 || elem->cyl->r > 255)
		return (-1);
	return (0);
}

int	cyl_pre_chkr(char **fl)
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
	if (digit_checker(fl[3]) || digit_checker(fl[4]))
		return (error_printer(3), 1);
	rgb = ft_split(fl[5], ',');
	if (ft_doublestrlen(rgb) != 3 || digit_checker(rgb[0])
		|| digit_checker(rgb[1]) || digit_checker(rgb[2]))
		return (error_printer(3), 1);
	return (0);
}

t_cyl	*cyl_creator(char **fl)
{
	char	**pos;
	char	**dir;
	char	**rgb;
	t_cyl	*cyl;

	cyl = malloc(sizeof(t_cyl));
	cyl->x = 0;
	if (fl[0][2] == 'x')
		cyl->x = 1;
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
