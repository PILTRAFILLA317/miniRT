/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:49:24 by becastro          #+#    #+#             */
/*   Updated: 2023/03/06 18:50:41 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

	return (rtn = vec_add(pos, vec_mult(dir, t)));
}
