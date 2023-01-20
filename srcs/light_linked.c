/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_linked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 14:19:49 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/20 18:48:28 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	light_checker(t_light light)
{
	if (light.bright < 0 || light.bright > 1)
		return (1);
	if (light.color.x < 0 || light.color.x > 255)
		return (1);
	if (light.color.y < 0 || light.color.y > 255)
		return (1);
	if (light.color.z < 0 || light.color.z > 255)
		return (1);
	return (0);
}

int	light_pre_chkr(char **fl)
{
	char	**pos;
	char	**rgb;

	pos = ft_split(fl[1], ',');
	if (ft_doublestrlen(pos) != 3 || digit_checker(pos[0])
		|| digit_checker(pos[1]) || digit_checker(pos[2]))
		return (error_printer(3), 1);
	if (digit_checker(fl[2]))
		return (error_printer(3), 1);
	rgb = ft_split(fl[3], ',');
	if (ft_doublestrlen(rgb) != 3 || digit_checker(rgb[0])
		|| digit_checker(rgb[1]) || digit_checker(rgb[2]))
		return (error_printer(3), 1);
	return (0);
}

t_light	*light_creator(char **fl, t_elem *e)
{
	char	**pos;
	char	**rgb;
	t_light	*light;

	light = malloc(sizeof(t_light));
	pos = ft_split(fl[1], ',');
	light->pos.x = ft_strtod(pos[0]) - e->cam.mtx.pos.x;
	light->pos.y = ft_strtod(pos[1]) - e->cam.mtx.pos.y;
	light->pos.z = ft_strtod(pos[2]) - e->cam.mtx.pos.z;
	light->bright = ft_strtod(fl[2]);
	rgb = ft_split(fl[3], ',');
	light->color.x = ft_atoi(rgb[0]);
	light->color.y = ft_atoi(rgb[1]);
	light->color.z = ft_atoi(rgb[2]);
	light->next = NULL;
	return (light);
}

int	new_light(t_elem *elem, t_light *new)
{
	t_light	*tmp;

	if (light_checker(*new))
		return (1);
	if (!elem->light)
	{
		elem->light = new;
		return (0);
	}
	tmp = elem->light;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}
