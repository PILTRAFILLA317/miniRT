/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:06:17 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 19:48:15 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	triangle_init(char **ver_pos, char **ver, t_tri *tri, t_elem *e)
{
	ver_pos = ft_split(ver[0], ',');
	tri->ver[0].x = ft_strtod(ver_pos[0]) - e->cam.mtx.pos.x;
	tri->ver[0].y = ft_strtod(ver_pos[1]) - e->cam.mtx.pos.y;
	tri->ver[0].z = ft_strtod(ver_pos[2]) - e->cam.mtx.pos.z;
	ver_pos = ft_split(ver[1], ',');
	tri->ver[1].x = ft_strtod(ver_pos[0]) - e->cam.mtx.pos.x;
	tri->ver[1].y = ft_strtod(ver_pos[1]) - e->cam.mtx.pos.y;
	tri->ver[1].z = ft_strtod(ver_pos[2]) - e->cam.mtx.pos.z;
	ver_pos = ft_split(ver[2], ',');
	tri->ver[2].x = ft_strtod(ver_pos[0]) - e->cam.mtx.pos.x;
	tri->ver[2].y = ft_strtod(ver_pos[1]) - e->cam.mtx.pos.y;
	tri->ver[2].z = ft_strtod(ver_pos[2]) - e->cam.mtx.pos.z;
}

t_tri	*triangle_creator(char **fl, t_elem *e)
{
	char	**ver;
	char	**ver_pos;
	char	**rgb;
	t_tri	*tri;
	t_vec	v[2];

	ver_pos = NULL;
	tri = malloc(sizeof(t_tri));
	ver = ft_split(fl[1], '|');
	triangle_init(ver_pos, ver, tri, e);
	v[0] = vec_diff(tri->ver[1], tri->ver[0]);
	v[1] = vec_diff(tri->ver[2], tri->ver[0]);
	tri->orient = vec_cross(v[0], v[1]);
	rgb = ft_split(fl[2], ',');
	tri->color.x = ft_atoi(rgb[0]);
	tri->color.y = ft_atoi(rgb[1]);
	tri->color.z = ft_atoi(rgb[2]);
	tri->next = NULL;
	return (tri);
}

int	new_triangle(t_elem *elem, t_tri *new)
{
	t_tri	*tmp;

	if (!elem->t)
	{
		elem->t = new;
		return (0);
	}
	tmp = elem->t;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
