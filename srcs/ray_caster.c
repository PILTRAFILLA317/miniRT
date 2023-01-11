/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/11 18:46:13 by umartin-         ###   ########.fr       */
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
	ld = sqrt((l.x * l.x) + (l.y * l.y) + (l.z * l.z));
	tca = (l.x * dir.x) + (l.y * dir.y) + (l.z * dir.z);
	if (dir.x == 0 && dir.y == 0 && dir.z == 1)
		printf ("TCA = %f\n", tca);
	if (tca < 0)
		return (0);
	d = sqrt((ld * ld) - (tca * tca));
	if (dir.x == 0 && dir.y == 0 && dir.z == 1)
		printf ("D = %f\n", d);
	if (d < (elem->sphere->diam / 2))
		return (1);
	return (0);
}

t_vec	vec_rotation(int x, int y, t_elem *elem)
{
	float	x_mid;
	float	y_mid;
	float	fov_mid;
	float	ang;
	t_vec	rtn;

	x_mid = WIN_X / 2;
	y_mid = WIN_Y / 2;
	fov_mid = elem->cam.fov / 2;
	ang = (fov_mid / x_mid) / (180 / M_PI);
	rtn.x = elem->cam.orient.x;
	rtn.y = (elem->cam.orient.y * cos(ang * (x - x_mid)))
		- (elem->cam.orient.z * sin(ang * (x - x_mid)));
	rtn.z = (elem->cam.orient.y * sin(ang * (x - x_mid)))
		+ (elem->cam.orient.z * cos(ang * (x - x_mid)));
	rtn.y = rtn.y;
	rtn.x = (rtn.x * cos(ang * (y - y_mid)))
		+ (rtn.z * sin(ang * (y - y_mid)));
	rtn.z = (-rtn.x * sin(ang * (y - y_mid)))
		+ (rtn.z * cos(ang * (y - y_mid)));
	if ((x == 960 && y == 540)
		|| (x == 961 && y == 540)
		|| (x == 0 && y == 0)
		|| (x == 1920 && y == 1080))
	{
		printf ("\nWIN_X = %d\n", x);
		printf ("WIN_Y = %d\n", y);
		printf ("X = %f\n", rtn.x);
		printf ("Y = %f\n", rtn.y);
		printf ("Z = %f\n", rtn.z);
		printf ("C X = %f\n", elem->cam.orient.x);
		printf ("C Y = %f\n", elem->cam.orient.y);
		printf ("C Z = %f\n", elem->cam.orient.z);
		printf ("ANG X = %f\n", ang * (x - x_mid));
		printf ("ANG Y = %f\n", ang * (y - y_mid));
		printf ("ANG = %f\n", ang);
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
