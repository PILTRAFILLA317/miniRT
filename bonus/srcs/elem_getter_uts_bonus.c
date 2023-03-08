/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_getter_uts_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:22:31 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:41:24 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

int	l_type(char **fl, t_elem *elem)
{
	if (ft_doublestrlen(fl) != 4 || light_pre_chkr(fl))
		return (error_printer(3), 1);
	if (new_light(elem, light_creator(fl, elem)))
		return (error_printer(3), 1);
	return (0);
}

int	pl_type(char **fl, t_elem *elem)
{
	if (ft_doublestrlen(fl) < 4
		|| ft_doublestrlen(fl) > 5
		|| plane_pre_chkr(fl))
		return (error_printer(3), 1);
	if (new_plane(elem, plane_creator(fl, elem)))
		return (error_printer(3), 1);
	return (0);
}

int	sp_type(char **fl, t_elem *elem)
{
	if (ft_doublestrlen(fl) < 4
		|| ft_doublestrlen(fl) > 5
		|| sphere_pre_chkr(fl))
		return (error_printer(3), 1);
	if (new_sphere(elem, sphere_creator(fl, elem)))
		return (error_printer(3), 1);
	return (0);
}

int	cy_type(char **fl, t_elem *elem)
{
	if (ft_doublestrlen(fl) != 6 || cyl_pre_chkr(fl))
		return (error_printer(3), 1);
	if (new_cyl(elem, cyl_creator(fl, elem)))
		return (error_printer(3), 1);
	return (0);
}

int	t_type(char **fl, t_elem *elem)
{
	if (new_triangle(elem, triangle_creator(fl, elem)))
		return (error_printer(3), 1);
	return (0);
}
