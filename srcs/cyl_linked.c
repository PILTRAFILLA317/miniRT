/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:07:38 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/19 17:03:23 by umartin-         ###   ########.fr       */
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
	if (elem->cyl->color.x < 0 || elem->cyl->color.x > 255)
		return (-1);
	if (elem->cyl->color.y< 0 || elem->cyl->color.y> 255)
		return (-1);
	if (elem->cyl->color.z < 0 || elem->cyl->color.x > 255)
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

t_cyl	*cyl_creator(char **fl, t_elem *e)
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
	cyl->pos.x = ft_strtod(pos[0]) - e->cam.mtx.pos.x;
	cyl->pos.y = ft_strtod(pos[1]) - e->cam.mtx.pos.y;
	cyl->pos.z = ft_strtod(pos[2]) - e->cam.mtx.pos.z;
	dir = ft_split(fl[2], ',');
	cyl->orient.x = ft_strtod(dir[0]);
	cyl->orient.y = ft_strtod(dir[1]);
	cyl->orient.z = ft_strtod(dir[2]);
	cyl->orient = vec_norm(cyl->orient);
	cyl->diam = ft_strtod(fl[3]);
	cyl->h = ft_strtod(fl[4]);
	cyl->pos2 = vec_point(cyl->orient, cyl->pos, cyl->h);
	rgb = ft_split(fl[5], ',');
	cyl->color.x = ft_atoi(rgb[0]);
	cyl->color.y= ft_atoi(rgb[1]);
	cyl->color.z = ft_atoi(rgb[2]);
	cyl->orient2 = vec_norm(points_to_vec(cyl->pos2, cyl->pos));
	cyl->bot_disc.color = cyl->color;
	cyl->bot_disc.diam = cyl->diam;
	cyl->bot_disc.orient = cyl->orient;
	cyl->bot_disc.pos = cyl->pos;
	cyl->top_disc.color = cyl->color;
	cyl->top_disc.diam = cyl->diam;
	cyl->top_disc.orient = cyl->orient2;
	cyl->top_disc.pos = cyl->pos2;
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
