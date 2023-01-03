/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sph_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 17:03:31 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/03 21:15:31 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_sphere	*sphere_creator(char **fl)
{
	char	    **pos;
	char	    **rgb;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
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
