/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/10 21:12:22 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_intersect(t_elem *elem, t_vec dir)
{
	t_vec	s_ro;
	t_vec	rd_t;
	t_vec	p;
	t_vec	s_p;
	//float	x;
	float	y;
	float	t;

	s_ro.x = elem->sphere->pos.x - elem->cam.pos.x;
	s_ro.y = elem->sphere->pos.y - elem->cam.pos.y;
	s_ro.z = elem->sphere->pos.z - elem->cam.pos.z;
	t = (s_ro.x * dir.x) + (s_ro.y
		* dir.y) + (s_ro.z * dir.z);
	rd_t.x = dir.x * t;
	rd_t.y = dir.y * t;
	rd_t.z = dir.z * t;
	p.x = elem->cam.pos.x + rd_t.x;
	p.y = elem->cam.pos.y + rd_t.y;
	p.z = elem->cam.pos.z + rd_t.z;
	s_p.x = elem->sphere->pos.x - p.x;
	s_p.y = elem->sphere->pos.y - p.y;
	s_p.z = elem->sphere->pos.z - p.z;
	y = sqrt((s_p.x * s_p.x) + (s_p.y * s_p.y) + (s_p.z * s_p.z));
	if (y < elem->sphere->diam)
	{
		// float x = sqrt (r*r - y*y) ;
		// float t1 = t-x;
		// float t2 = t+x;
		// float cremap01 (s.z, s.z-r, t1);
		return (1);
	}
	return (0);
}

t_vec	vec_rotation(int x, int y, t_elem *elem)
{
	float	x_mid;
	float	y_mid;
	float	fov_mid;
	double	ang;
	t_vec	rtn;

	(void)y;
	(void)x;
	x_mid = WIN_X / 2;
	y_mid = WIN_Y / 2;
	fov_mid = elem->cam.fov / 2;
	ang = fov_mid / x_mid;
	rtn.x = elem->cam.orient.x;
	rtn.y = (elem->cam.orient.y * cos(ang * (x - x_mid))) - (elem->cam.orient.z * sin(ang * (x - x_mid)));
	rtn.z = (elem->cam.orient.y * sin(ang * (x - x_mid))) + (elem->cam.orient.z * cos(ang * (x - x_mid)));
	rtn.y = rtn.y;
	rtn.x = (rtn.x * cos(ang * (y - y_mid))) + (rtn.z * sin(ang * (y - y_mid)));
	rtn.z = (-rtn.x * sin(ang * (y - y_mid))) + (rtn.z * cos(ang * (y - y_mid)));
	// rtn.y = elem->cam.orient.y;
	// rtn.x = (elem->cam.orient.x * cos(ang * (y - y_mid))) + (elem->cam.orient.z * sin(ang * (y - y_mid)));
	// rtn.z = (-elem->cam.orient.x * sin(ang * (y - y_mid))) + (elem->cam.orient.z * cos(ang * (y - y_mid)));
	// rtn.z = elem->cam.orient.z;
	// rtn.x = (elem->cam.orient.x * cos(ang * (x - x_mid))) - (elem->cam.orient.y * sin(ang * (x - x_mid)));
	// rtn.y = (elem->cam.orient.x * sin(ang * (x - x_mid))) + (elem->cam.orient.y * cos(ang * (x - x_mid)));
	// printf ("\nX = %d ", x);
	// printf ("Y = %d\n", y);
	// printf ("ANG X= %f\n", ang * (x - x_mid));
	// printf ("ANG Y= %f\n", ang * (y - y_mid));
	// printf ("VEC X= %f\n", rtn.x);
	// printf ("VEC Y= %f\n", rtn.y);
	// printf ("VEC Z= %f\n", rtn.z);
	// printf ("NORM= %f\n", sqrt((rtn.x * rtn.x) + (rtn.y * rtn.y) + (rtn.z * rtn.z)));
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
