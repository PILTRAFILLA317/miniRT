/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:52:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 18:50:29 by becastro         ###   ########.fr       */
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

t_vec	vec_mult_vec(t_vec a, t_vec b)
{
	t_vec	rtn;

	rtn.x = a.x * b.x;
	rtn.y = a.y * b.y;
	rtn.z = a.z * b.z;
	return (rtn);
}

double	clamp(double min, double max, double value)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

t_vec	vec_clamp(double min, double max, t_vec value)
{
	t_vec	rtn;

	rtn.x = clamp(min, max, value.x);
	rtn.y = clamp(min, max, value.y);
	rtn.z = clamp(min, max, value.z);
	return (rtn);
}

t_vec	vec_unit(t_vec vec)
{
	t_vec	rtn;
	double	mod;

	mod = vec_len(vec);
	rtn = vec_div(vec, mod);
	return(rtn);
}

t_vec	vec_cross(t_vec v, t_vec w)
{
	t_vec	u;

	u.x = (v.y * w.z) - (v.z * w.y);
	u.y = (v.z * w.x) - (v.x * w.z);
	u.z = (v.x * w.y) - (v.y * w.x);
	return (u);
}
