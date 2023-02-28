/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   con_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:23:28 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/28 18:48:10 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	con_intersect_point(t_vec pos, t_con *con, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	alpha;
	double	t;
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec	delt;

	delt = vec_diff(con->pos, pos);
	tmp1.x = dir.x - (vec_dot(dir, con->orient) * con->orient.x);
	tmp1.y = dir.y - (vec_dot(dir, con->orient) * con->orient.y);
	tmp1.z = dir.z - (vec_dot(dir, con->orient) * con->orient.z);
	tmp2.x = (delt.x) - (vec_dot(delt, con->orient) * con->orient.x);
	tmp2.y = (delt.y) - (vec_dot(delt, con->orient) * con->orient.y);
	tmp2.z = (delt.z) - (vec_dot(delt, con->orient) * con->orient.z);
	alpha = con->ang * (M_PI / 180);
	a = (pow(cos(alpha), 2) * vec_dot(tmp1, tmp1)) - (pow(sin(alpha), 2) * vec_dot(dir, con->orient));
	b = 2 * ((pow(cos(alpha), 2) * vec_dot(tmp1, tmp2)) - (pow(sin(alpha), 2) * vec_dot(dir, con->orient) * vec_dot(delt, con->orient)));
	c = (pow(cos(alpha), 2) * vec_dot(tmp2, tmp2)) - (pow(sin(alpha), 2) * vec_dot(delt, con->orient));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t = (b - sqrt(d)) / (2 * a);
		return (vec_point(dir, pos, t));
	}
	return (con->pos);
}

int	con_intersect(t_vec pos, t_con *con, t_vec dir)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	alpha;
	double	t;
	double	a1;
	t_vec	p;
	t_vec	tmp1;
	t_vec	tmp2;
	t_vec	delt;

	delt = vec_diff(con->pos, pos);
	tmp1.x = dir.x - (vec_dot(dir, con->orient) * con->orient.x);
	tmp1.y = dir.y - (vec_dot(dir, con->orient) * con->orient.y);
	tmp1.z = dir.z - (vec_dot(dir, con->orient) * con->orient.z);
	tmp2.x = (delt.x) - (vec_dot(delt, con->orient) * con->orient.x);
	tmp2.y = (delt.y) - (vec_dot(delt, con->orient) * con->orient.y);
	tmp2.z = (delt.z) - (vec_dot(delt, con->orient) * con->orient.z);
	alpha = con->ang * (M_PI / 180);
	a = (pow(cos(alpha), 2) * vec_dot(tmp1, tmp1)) - (pow(sin(alpha), 2) * vec_dot(dir, con->orient));
	b = 2 * ((pow(cos(alpha), 2) * vec_dot(tmp1, tmp2)) - (pow(sin(alpha), 2) * vec_dot(dir, con->orient) * vec_dot(delt, con->orient)));
	c = (pow(cos(alpha), 2) * vec_dot(tmp2, tmp2)) - (pow(sin(alpha), 2) * vec_dot(delt, con->orient));
	d = b * b - 4 * a * c;
	if (d >= 0)
	{
		t = (b - sqrt(d)) / (2 * a);
		if (t > 0)
		{
			p = vec_point(dir, pos, t);
			a1 = vec_dot(vec_norm(points_to_vec(con->pos, p)), con->orient);
			if (a1 >= 0)
				return (1);
		}
	}
	return (0);
}
