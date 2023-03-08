/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:52:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:44:36 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

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