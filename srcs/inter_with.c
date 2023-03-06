/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_w.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:17:28 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/20 17:38:21 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	i_w_sph(t_elem *elem, t_dirpos arg, t_sphere sph, t_light light)
{
	if (iw_sph_s_it(elem, arg, sph, light))
		return (1);
	if (iw_sph_c_it(elem, arg, light))
		return (1);
	if (iw_sph_p_it(elem, arg, light))
		return (1);
	if (iw_sph_t_it(elem, arg, light))
		return (1);
	return (0);
}

int	i_w_cyl(t_elem *elem, t_dirpos arg, t_cyl cyl, t_light light)
{
	if (iw_cyl_s_it(elem, arg, light))
		return (1);
	if (iw_cyl_c_it(elem, arg, cyl, light))
		return (1);
	if (iw_cyl_p_it(elem, arg, light))
		return (1);
	if (iw_cyl_t_it(elem, arg, light))
		return (1);
	return (0);
}

int	i_w_pl(t_elem *elem, t_dirpos arg, t_plane pl, t_light light)
{
	if (iw_pl_s_it(elem, arg, light))
		return (1);
	if (iw_pl_c_it(elem, arg, light))
		return (1);
	if (iw_pl_p_it(elem, arg, pl, light))
		return (1);
	if (iw_pl_t_it(elem, arg, light))
		return (1);
	return (0);
}

int	i_w_disc(t_elem *elem, t_dirpos arg, t_disc disc, t_light light)
{
	if (iw_disc_s_it(elem, arg, light))
		return (1);
	if (iw_disc_c_it(elem, arg, disc, light))
		return (1);
	if (iw_disc_p_it(elem, arg, light))
		return (1);
	if (iw_disc_t_it(elem, arg, light))
		return (1);
	return (0);
}

int	i_w_tri(t_elem *elem, t_dirpos arg, t_tri tri, t_light light)
{
	if (iw_tri_s_it(elem, arg, light))
		return (1);
	if (iw_tri_c_it(elem, arg, light))
		return (1);
	if (iw_tri_p_it(elem, arg, light))
		return (1);
	if (iw_tri_t_it(elem, tri, arg, light))
		return (1);
	return (0);
}
