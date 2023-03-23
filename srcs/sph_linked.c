/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:31 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/23 19:13:03 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	sphere_checker(t_sphere sphere)
{
	if (sphere.color.x < 0 || sphere.color.x > 255
		|| sphere.color.y < 0 || sphere.color.y > 255
		|| sphere.color.z < 0 || sphere.color.x > 255)
		return (1);
	return (0);
}

int	sphere_pre_chkr(char **fl)
{
	char	**pos;
	char	**rgb;

	pos = ft_split(fl[1], ',');
	if (ft_doublestrlen(pos) != 3 || digit_checker(pos[0])
		|| digit_checker(pos[1]) || digit_checker(pos[2]))
		return (1);
	if (digit_checker(fl[2]))
		return (1);
	rgb = ft_split(fl[3], ',');
	if (ft_doublestrlen(rgb) != 3 || digit_checker(rgb[0])
		|| digit_checker(rgb[1]) || digit_checker(rgb[2]))
		return (1);
	return (0);
}

t_sphere	*sphere_creator(char **fl, t_elem *e)
{
	char		**pos;
	char		**rgb;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (fl[4])
		sphere->x = 1;
	else
		sphere->x = 0;
	pos = ft_split(fl[1], ',');
	sphere->pos.x = ft_strtod(pos[0]) - e->cam.mtx.pos.x;
	sphere->pos.y = ft_strtod(pos[1]) - e->cam.mtx.pos.y;
	sphere->pos.z = ft_strtod(pos[2]) - e->cam.mtx.pos.z;
	sphere->diam = ft_strtod(fl[2]);
	rgb = ft_split(fl[3], ',');
	sphere->color.x = ft_atoi(rgb[0]);
	sphere->color.y = ft_atoi(rgb[1]);
	sphere->color.z = ft_atoi(rgb[2]);
	if (fl[4] != NULL)
		sphere->ref = ft_strtod(fl[4]);
	sphere->next = NULL;
	return (sphere);
}

int	new_sphere(t_elem *elem, t_sphere *new)
{
	t_sphere	*tmp;

	if (sphere_checker(*new))
		return (1);
	if (!elem->sphere)
	{
		elem->sphere = new;
		return (0);
	}
	tmp = elem->sphere;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
