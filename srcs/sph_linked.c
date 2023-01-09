/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:31 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/09 19:41:11 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	sphere_checker(t_elem *elem)
{
	if (elem->sphere->r < 0 || elem->sphere->r > 255)
		return (-1);
	if (elem->sphere->g < 0 || elem->sphere->g > 255)
		return (-1);
	if (elem->sphere->b < 0 || elem->sphere->r > 255)
		return (-1);
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

t_sphere	*sphere_creator(char **fl)
{
	char		**pos;
	char		**rgb;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (fl[0][2] == 'x')
		sphere->x = 1;
	else
		sphere->x = 0;
	pos = ft_split(fl[1], ',');
	sphere->pos.x = ft_strtod(pos[0]);
	sphere->pos.y = ft_strtod(pos[1]);
	sphere->pos.z = ft_strtod(pos[2]);
	sphere->diam = ft_strtod(fl[2]);
	rgb = ft_split(fl[3], ',');
	sphere->r = ft_atoi(rgb[0]);
	sphere->g = ft_atoi(rgb[1]);
	sphere->b = ft_atoi(rgb[2]);
	sphere->next = NULL;
	return (sphere);
}

void	new_sphere(t_sphere **lst, t_sphere *new)
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
