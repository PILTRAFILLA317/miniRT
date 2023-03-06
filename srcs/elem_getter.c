/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:28:48 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 19:47:45 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	elem_type(char *line, t_elem *elem)
{
	char	**fl;

	if (line[ft_strlen(line) - 1] == '\n')
		line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (line[0] == 'L')
	{
		if (ft_doublestrlen(fl) != 4 || light_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_light(elem, light_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 'p' && line[1] == 'l')
	{
		if (ft_doublestrlen(fl) < 4
			|| ft_doublestrlen(fl) > 5
			|| plane_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_plane(elem, plane_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 's' && line[1] == 'p')
	{
		if (ft_doublestrlen(fl) < 4
			|| ft_doublestrlen(fl) > 5
			|| sphere_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_sphere(elem, sphere_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 'c' && line[1] == 'y')
	{
		if (ft_doublestrlen(fl) != 6 || cyl_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_cyl(elem, cyl_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 't')
	{
		if (new_triangle(elem, triangle_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else
		return (error_printer(3), 1);
	return (0);
}
