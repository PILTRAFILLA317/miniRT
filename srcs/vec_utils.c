/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:52:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/19 17:12:53 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	vec_selfdot(t_vec a)
{
	return ((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

double	vec_dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vec_len(t_vec vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_vec	vec_norm(t_vec vec)
{
	t_vec	rtn;
	double	len;

	len = vec_len(vec);
	if (len == 0)
		return (vec);
	rtn.x = vec.x / len;
	rtn.y = vec.y / len;
	rtn.z = vec.z / len;
	return (rtn);
}

t_vec	points_to_vec(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = b.x - a.x;
	rtn.y = b.y - a.y;
	rtn.z = b.z - a.z;
	return (rtn);
}

t_vec	vec_diff(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.x - b.x;
	rtn.y = a.y - b.y;
	rtn.z = a.z - b.z;
	return (rtn);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.x + b.x;
	rtn.y = a.y + b.y;
	rtn.z = a.z + b.z;
	return (rtn);
}

t_vec	vec_mult(t_vec vec, double a)
{
	t_vec	rtn;

	rtn.x = vec.x * a;
	rtn.y = vec.y * a;
	rtn.z = vec.z * a;
	return (rtn);
}

t_vec	vec_div(t_vec vec, double a)
{
	t_vec	rtn;

	rtn.x = vec.x / a;
	rtn.y = vec.y / a;
	rtn.z = vec.z / a;
	return (rtn);
}

t_vec	vec_point(t_vec dir, t_vec pos, double t)
{
	t_vec	rtn;

	return(rtn = vec_add(pos, vec_mult(dir, t)));
}

void	vec_printer(t_vec	vec)
{
	printf("[%lf][%lf][%lf]\n", vec.x, vec.y, vec.z);
}

t_vec	new_vec(double x, double y, double z)
{
	t_vec	rtn;

	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}
