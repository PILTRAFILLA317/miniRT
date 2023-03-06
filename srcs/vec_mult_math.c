/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:51:34 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 18:52:09 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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
