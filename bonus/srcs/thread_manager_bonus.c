/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manager_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:56:01 by becastro          #+#    #+#             */
/*   Updated: 2023/03/08 17:43:46 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

void	thread_loop(t_th_vars *th_v, int *i, int *r, t_th th)
{
	while (++i[1] <= i[0])
	{
		i[2] = -1;
		while (++i[2] <= WIN_X)
		{
			th_v->xx = (double)i[2] * 2 / WIN_X - 1;
			th_v->yy = 1 - (double)i[1] * 2 / WIN_Y;
			th_v->d.pos = th.elem->cam.pos;
			th_v->d.dir = vec_rotation(th_v->xx, th_v->yy, th.elem);
			r[i[4]] = 0;
			i[3] = color(th.elem, th_v->d, th_v->obj, &r[i[4]]);
			pthread_mutex_lock(&th.elem->pixl);
			mlx_pixel_put(th.elem->mlx, th.elem->win, i[2], i[1], i[3]);
			pthread_mutex_unlock(&th.elem->pixl);
			i[4]++;
		}
	}
}

void	*thread_routine(void *data)
{
	t_th		th;
	t_th_vars	th_v;
	int			i[5];
	int			*r;

	th = *(t_th *)data;
	th_v.obj.type = n;
	i[0] = (WIN_Y / NUM_THREAD * th.core) + (WIN_Y / NUM_THREAD);
	i[1] = WIN_Y / NUM_THREAD * th.core - 1;
	r = malloc(sizeof(int) * ((i[0] - i[1] + 1) * (WIN_X - i[2] + 1)) + 1);
	i[4] = 0;
	thread_loop(&th_v, i, r, th);
	return (NULL);
}
