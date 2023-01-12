/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:52:04 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/12 20:53:05 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	vec_dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vec_scalar(t_vec a, t_vec b)
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
	rtn.x = vec.x / len;
	rtn.y = vec.y / len;
	rtn.z = vec.z / len;
	return (rtn);
}
