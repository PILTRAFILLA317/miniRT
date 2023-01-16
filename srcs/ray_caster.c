/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/16 20:41:22 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_intersect(t_elem *elem, t_vec dir)
{
	t_vec	l;
	float	ld;
	float	tca;
	float	d;

	l.x = elem->sphere->pos.x - elem->cam.pos.x;
	l.y = elem->sphere->pos.y - elem->cam.pos.y;
	l.z = elem->sphere->pos.z - elem->cam.pos.z;
	ld = vec_len(l);
	tca = vec_dot(l, dir);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (d < (elem->sphere->diam / 2))
		return (1);
	return (0);
}

t_vec	vec_rotation(int x, int y, t_elem *elem)
{
	t_vec	rtn;
	double	imageaspectratio;
	double	px;
	double	py;

	imageaspectratio = WIN_X / WIN_Y;
	px = (2 * ((x + 0.5) / WIN_X) - 1)
		* tan(elem->cam.fov / 2 * (M_PI / 180)) * imageaspectratio;
	py = (1 - 2 * ((y + 0.5) / WIN_Y)) * tan(elem->cam.fov / 2 * (M_PI / 180));
	rtn.x = px;
	rtn.y = py;
	rtn.z = 1;
	rtn = vec_norm (rtn);
	return (rtn);
}

void	ray_caster(t_elem *elem)
{
	int	x;
	int	y;

	x = 0;
	while (x <= WIN_X)
	{
		y = 0;
		while (y <= WIN_Y)
		{
			if (ft_intersect(elem, vec_rotation(x, y, elem)) == 1)
				mlx_pixel_put(elem->mlx, elem->win, x, y, 0x0000FF00);
			y++;
		}
		x++;
	}
}
