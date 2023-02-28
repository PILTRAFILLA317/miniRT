/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:26 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/28 17:25:26 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	con_checker(t_con con)
{
	if (con.orient.x < -1 || con.orient.x > 1)
		return (1);
	if (con.orient.y < -1 || con.orient.y > 1)
		return (1);
	if (con.orient.z < -1 || con.orient.z > 1)
		return (1);
	if (con.color.x < 0 || con.color.x > 255)
		return (1);
	if (con.color.y < 0 || con.color.y > 255)
		return (1);
	if (con.color.z < 0 || con.color.x > 255)
		return (1);
	return (0);
}

int	con_pre_chkr(char **fl)
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

t_con	*cone_creator(char **fl, t_elem *e)
{
	char	**pos;
	char	**dir;
	char	**rgb;
	t_con	*con;

	con = malloc(sizeof(t_con));
	pos = ft_split(fl[1], ',');
	con->pos.x = ft_strtod(pos[0]) - e->cam.mtx.pos.x;
	con->pos.y = ft_strtod(pos[1]) - e->cam.mtx.pos.y;
	con->pos.z = ft_strtod(pos[2]) - e->cam.mtx.pos.z;
	dir = ft_split(fl[2], ',');
	con->orient.x = ft_strtod(dir[0]);
	con->orient.y = ft_strtod(dir[1]);
	con->orient.z = ft_strtod(dir[2]);
	con->orient = vec_norm(con->orient);
	con->ang = ft_strtod(fl[3]);
	rgb = ft_split(fl[4], ',');
	con->color.x = ft_atoi(rgb[0]);
	con->color.y = ft_atoi(rgb[1]);
	con->color.z = ft_atoi(rgb[2]);
	con->next = NULL;
	return (con);
}

int	new_cone(t_elem *elem, t_con *new)
{
	t_con	*tmp;

	// if (con_checker(*new))
	// 	return (1);
	if (!elem->con)
	{
		elem->con = new;
		return (0);
	}
	tmp = elem->con;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
