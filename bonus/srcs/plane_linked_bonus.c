/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_linked_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:30:52 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/23 18:42:59 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

int	plane_checker(t_plane pl)
{
	if (pl.orient.x < -1 || pl.orient.x > 1)
		return (1);
	if (pl.orient.y < -1 || pl.orient.y > 1)
		return (1);
	if (pl.orient.z < -1 || pl.orient.z > 1)
		return (1);
	if (pl.color.x < 0 || pl.color.x > 255)
		return (1);
	if (pl.color.y < 0 || pl.color.y > 255)
		return (1);
	if (pl.color.z < 0 || pl.color.x > 255)
		return (1);
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

void	plane_pos_init(t_plane *plane, t_elem *e, char **fl, char **pos)
{
	pos = ft_split(fl[1], ',');
	plane->pos.x = ft_strtod(pos[0]) - e->cam.mtx.pos.x;
	plane->pos.y = ft_strtod(pos[1]) - e->cam.mtx.pos.y;
	plane->pos.z = ft_strtod(pos[2]) - e->cam.mtx.pos.z;
}

t_plane	*plane_creator(char **fl, t_elem *e)
{
	char	**pos;
	char	**dir;
	char	**rgb;
	t_plane	*plane;

	pos = NULL;
	plane = malloc(sizeof(t_plane));
	plane->x = 0;
	if (fl[0][2] == 'x')
		plane->x = 1;
	else if (fl[0][2] == 'c')
		plane->x = 2;
	plane_pos_init(plane, e, fl, pos);
	dir = ft_split(fl[2], ',');
	plane->orient.x = ft_strtod(dir[0]);
	plane->orient.y = ft_strtod(dir[1]);
	plane->orient.z = ft_strtod(dir[2]);
	rgb = ft_split(fl[3], ',');
	plane->color.x = ft_atoi(rgb[0]);
	plane->color.y = ft_atoi(rgb[1]);
	plane->color.z = ft_atoi(rgb[2]);
	if (fl[4] != NULL)
		plane->ref = ft_strtod(fl[4]);
	plane->next = NULL;
	return (plane);
}

int	new_plane(t_elem *elem, t_plane *new)
{
	t_plane	*tmp;

	if (plane_checker(*new))
		return (1);
	if (!elem->pl)
	{
		elem->pl = new;
		return (0);
	}
	tmp = elem->pl;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
