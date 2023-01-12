/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/12 21:03:32 by umartin-         ###   ########.fr       */
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
	tca = vec_scalar(l, dir);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (d < (elem->sphere->diam / 2))
		return (1);
	return (0);
}

t_vec	vec_rotation(int x, int y, t_elem *elem)
{
	float	fov_mid;
	float	ang_x;
	float	ang_y;
	t_vec	rtn;

	fov_mid = elem->cam.fov / 2;
	ang_x = (fov_mid / (WIN_X / 2)) / (180 / M_PI) * (x - (WIN_X / 2));
	ang_y = (fov_mid / (WIN_Y / 2)) / (180 / M_PI) * (y - (WIN_Y / 2));
	rtn.x = elem->cam.orient.x;
	rtn.y = (elem->cam.orient.y * cos(ang_y))
		- (elem->cam.orient.z * sin(ang_y));
	rtn.z = (elem->cam.orient.y * sin(ang_y))
		+ (elem->cam.orient.z * cos(ang_y));
	rtn.x = (rtn.x * cos(ang_x))
		+ (rtn.z * sin(ang_x));
	rtn.y = rtn.y;
	rtn.z = (-rtn.x * sin(ang_x))
		+ (rtn.z * cos(ang_x));
	vec_norm (rtn);
	if (x == 0 && y == 540)
	{
		printf ("\nWIN_X = %d\n", x);
		printf ("WIN_Y = %d\n", y);
		printf ("X = %f\n", rtn.x);
		printf ("Y = %f\n", rtn.y);
		printf ("Z = %f\n", rtn.z);
		printf ("C X = %f\n", elem->cam.orient.x);
		printf ("C Y = %f\n", elem->cam.orient.y);
		printf ("C Z = %f\n", elem->cam.orient.z);
	}
	return (rtn);
}

void	ray_caster(t_elem *elem)
{
	int	x;
	int	y;

	// if (ft_intersect(elem) == 1)
	// 	mlx_pixel_put(elem->mlx, elem->win, 0, 0, 0x0000FF00);
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
