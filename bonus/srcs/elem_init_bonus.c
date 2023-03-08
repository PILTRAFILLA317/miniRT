/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:55:15 by becastro          #+#    #+#             */
/*   Updated: 2023/03/08 17:41:28 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

void	init_elem_cam(t_elem *elem, char **pos)
{
	elem->cam.mtx.pos.x = ft_strtod(pos[0]);
	elem->cam.pos.x = 0;
	elem->cam.mtx.pos.y = ft_strtod(pos[1]);
	elem->cam.pos.y = 0;
	elem->cam.mtx.pos.z = ft_strtod(pos[2]);
	elem->cam.pos.z = 0;
}

void	init_elem_orient(t_elem *elem, char **rot, char **fl)
{
	elem->cam.orient.x = ft_strtod(rot[0]);
	elem->cam.orient.y = ft_strtod(rot[1]);
	elem->cam.orient.z = ft_strtod(rot[2]);
	elem->cam.orient = vec_norm(elem->cam.orient);
	elem->cam.a_ratio = (double)WIN_X / (double)WIN_Y;
	elem->cam.fov = ft_strtod(fl[3]);
	elem->cam.theta = elem->cam.fov * M_PI / 180.0;
	elem->cam.w = tan(elem->cam.fov * M_PI / 360.0);
	elem->cam.h = elem->cam.w / WIN_X * WIN_Y;
	if ((elem->cam.orient.x == 0 && elem->cam.orient.y == 1
			&& elem->cam.orient.z == 0)
		|| (elem->cam.orient.x == 0 && elem->cam.orient.y == -1
			&& elem->cam.orient.z == 0))
		elem->cam.up = new_vec(0.0, 0.0, 1.0);
	else
		elem->cam.up = new_vec(0.0, 1.0, 0.0);
	elem->cam.right = vec_mult(
			vec_norm(vec_cross(elem->cam.orient, elem->cam.up)), -1);
	elem->cam.up = vec_mult(
			vec_norm(vec_cross(elem->cam.right, elem->cam.orient)), -1);
}
