/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   al_cam_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:50:21 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/24 18:47:59 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	alight_checker(t_elem *elem)
{
	if (elem->alight.ratio < 0 || elem->alight.ratio > 1)
		return (-1);
	if (elem->alight.color.x < 0 || elem->alight.color.x > 255)
		return (-1);
	if (elem->alight.color.y < 0 || elem->alight.color.y > 255)
		return (-1);
	if (elem->alight.color.z < 0 || elem->alight.color.z > 255)
		return (-1);
	return (0);
}

int	cam_checker(t_elem *elem)
{
	if (elem->cam.orient.x < -1 || elem->cam.orient.x > 1)
		return (-1);
	if (elem->cam.orient.y < -1 || elem->cam.orient.y > 1)
		return (-1);
	if (elem->cam.orient.z < -1 || elem->cam.orient.x > 1)
		return (-1);
	if (elem->cam.fov < 0 || elem->cam.fov > 180)
		return (-1);
	return (0);
}

int	first_line_alight(char *line, t_elem *elem)
{
	char	**fl;
	char	**rgb;

	line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (fl[0][0] != 'A' || ft_doublestrlen(fl) != 3)
		return (error_printer(3), 1);
	if (digit_checker(fl[1]))
		return (error_printer(3), 1);
	elem->alight.ratio = ft_strtod(fl[1]);
	rgb = ft_split(fl[2], ',');
	if (ft_doublestrlen(rgb) != 3 || digit_checker(rgb[0])
		|| digit_checker(rgb[1]) || digit_checker(rgb[2]))
		return (error_printer(3), 1);
	elem->alight.color.x = ft_atoi(rgb[0]);
	elem->alight.color.y = ft_atoi(rgb[1]);
	elem->alight.color.z = ft_atoi(rgb[2]);
	if (alight_checker(elem) == -1)
		return (1);
	ft_doublefree(fl);
	ft_doublefree(rgb);
	return (0);
}

int	second_line_cam(char *line, t_elem *elem)
{
	char	**fl;
	char	**pos;
	char	**rot;

	fl = ft_split(line, ' ');
	if (fl[0][0] != 'C' || ft_doublestrlen(fl) != 4)
		return (error_printer(3), 1);
	pos = ft_split(fl[1], ',');
	if (ft_doublestrlen(pos) != 3 || digit_checker(pos[0])
		|| digit_checker(pos[1]) || digit_checker(pos[2]))
		return (error_printer(3), 1);
	elem->cam.mtx.pos.x = ft_strtod(pos[0]);
	elem->cam.pos.x = 0;
	elem->cam.mtx.pos.y = ft_strtod(pos[1]);
	elem->cam.pos.y = 0;
	elem->cam.mtx.pos.z = ft_strtod(pos[2]);
	elem->cam.pos.z = 0;
	rot = ft_split(fl[2], ',');
	if (ft_doublestrlen(rot) != 3 || digit_checker(rot[0])
		|| digit_checker(rot[1]) || digit_checker(rot[2]))
		return (error_printer(3), 1);
	elem->cam.orient.x = ft_strtod(rot[0]);
	elem->cam.orient.y = ft_strtod(rot[1]);
	elem->cam.orient.z = ft_strtod(rot[2]);
	elem->cam.orient = vec_norm(elem->cam.orient);
	elem->cam.fov = ft_strtod(fl[3]);
	if (cam_checker(elem) == -1)
		return (1);
	return (0);
}
