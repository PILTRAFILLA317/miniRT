/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/02 16:10:03 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	vec_rotation(double x, double y, t_elem *elem)
{
	t_vec	rtn;
	t_vec	right;
	t_vec	up;

	right = vec_mult(elem->cam.right, x * elem->cam.w);
	up = vec_mult(elem->cam.up, y * elem->cam.h);
	rtn = vec_add(vec_add(right, up), elem->cam.orient);
	rtn = vec_norm (rtn);
	return (rtn);
}

t_object	first_intersect(t_elem *elem, t_vec dir, t_vec pos, t_object co)
{
	t_objlen	ol;
	t_dirpos	dp;

	dp.dir = dir;
	dp.pos = pos;
	ol.len = 0;
	ol.obj.elem = NULL;
	ol = cyl_f_i(elem, dp, ol);
	ol = pl_f_i(elem, dp, co, ol);
	ol = sph_f_i(elem, dp, co, ol);
	ol = tri_f_i(elem, dp, ol);
	return (ol.obj);
}

int	color(t_elem *elem, t_dirpos dp, t_object co, int *ray)
{
	t_object	obj;

	obj = first_intersect(elem, dp.dir, dp.pos, co);
	if (obj.elem == NULL)
		return (0);
	if (obj.type == c)
		return (cyl_color(elem, dp.dir, dp.pos, (*(t_cyl *)obj.elem)));
	if (obj.type == d)
		return (disc_color(elem, dp.dir, dp.pos, (*(t_disc *)obj.elem)));
	if (obj.type == s)
		return (sph_color(elem, dp, (*(t_sphere *)obj.elem), ray));
	if (obj.type == p)
		return (plane_color(elem, dp, (*(t_plane *)obj.elem), ray));
	if (obj.type == t)
		return (trian_color(elem, dp.dir, dp.pos, (*(t_tri *)obj.elem)));
	return (0);
}

void	*thread_routine(void *data)
{
	t_th		th;
	int			i[5];
	int			*r;
	double		xx;
	double		yy;
	t_object	obj;
	t_dirpos	d;

	th = *(t_th *)data;
	obj.type = n;
	i[0] = (WIN_Y / NUM_THREAD * th.core) + (WIN_Y / NUM_THREAD);
	i[1] = WIN_Y / NUM_THREAD * th.core - 1;
	r = malloc(sizeof(int) * ((i[0] - i[1] + 1) * (WIN_X - i[2] + 1)) + 1);
	i[4] = 0;
	while (++i[1] <= i[0])
	{
		i[2] = -1;
		while (++i[2] <= WIN_X)
		{
			xx = (double)i[2] * 2 / WIN_X - 1;
			yy = 1 - (double)i[1] * 2 / WIN_Y;
			d.pos = th.elem->cam.pos;
			d.dir = vec_rotation(xx, yy, th.elem);
			r[i[4]] = 0;
			i[3] = color(th.elem, d, obj, &r[i[4]]);
			pthread_mutex_lock(&th.elem->pixl);
			mlx_pixel_put(th.elem->mlx, th.elem->win, i[2], i[1], i[3]);
			pthread_mutex_unlock(&th.elem->pixl);
			i[4]++;
		}
	}
	return (NULL);
}

void	ray_caster(t_elem *elem)
{
	int	i;

	i = -1;
	elem->th = (t_th *)malloc(sizeof(t_th) * NUM_THREAD);
	pthread_mutex_init(&elem->pixl, 0);
	while (++i < NUM_THREAD)
	{
		elem->th[i].elem = elem;
		elem->th[i].core = i;
		if (pthread_create(&elem->th[i].th, NULL, thread_routine,
				&elem->th[i]) != 0)
			printf("WUAAAAAA");
	}
	i = -1;
	while (++i < NUM_THREAD)
		if (pthread_join(elem->th[i].th, NULL))
			printf("WUAAAAAA");
}
