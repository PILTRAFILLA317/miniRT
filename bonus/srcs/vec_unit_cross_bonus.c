/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_unit_cross_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 18:53:34 by becastro          #+#    #+#             */
/*   Updated: 2023/03/08 17:44:32 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

t_vec	vec_unit(t_vec vec)
{
	t_vec	rtn;
	double	mod;

	mod = vec_len(vec);
	rtn = vec_div(vec, mod);
	return (rtn);
}

t_vec	vec_cross(t_vec v, t_vec w)
{
	t_vec	u;

	u.x = (v.y * w.z) - (v.z * w.y);
	u.y = (v.z * w.x) - (v.x * w.z);
	u.z = (v.x * w.y) - (v.y * w.x);
	return (u);
}
