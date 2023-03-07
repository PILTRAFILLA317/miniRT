/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:50:33 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/07 13:46:33 by umartin-         ###   ########.fr       */
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
			exit (1);
	}
	i = -1;
	while (++i < NUM_THREAD)
		if (pthread_join(elem->th[i].th, NULL))
			exit (1);
}
