/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creators.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:03:33 by becastro          #+#    #+#             */
/*   Updated: 2023/03/07 16:15:04 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

t_ver	*trian_creator(char **fl)
{
	t_ver	*trian;

	trian = malloc(sizeof(t_ver));
	trian->ver.x = fl[1];
	trian->ver.y = fl[2];
	trian->ver.z = fl[3];
	trian->next = NULL;
	return (trian);
}

t_norm	*norm_creator(char **fl)
{
	t_norm	*trian;

	trian = malloc(sizeof(t_ver));
	trian->norm.x = last_char_trimmer(fl[1]);
	trian->norm.y = last_char_trimmer(fl[2]);
	trian->norm.z = last_char_trimmer(fl[3]);
	trian->next = NULL;
	return (trian);
}

t_tri	*face_creator(char **fl, t_ver **ver)
{
	t_tri	*trian;
	t_ver	*temp;
	char	**sp;
	int		c;
	int		end;

	trian = malloc(sizeof(t_tri));
	sp = ft_split(fl[0], '/');
	end = ft_atoi(sp[0]) - 1;
	temp = *ver;
	c = -1;
	while (++c < end)
		temp = temp->next;
	trian->vert[0] = temp->ver;
	free(sp);
	sp = ft_split(fl[1], '/');
	end = ft_atoi(sp[0]) - 1;
	temp = *ver;
	c = -1;
	while (++c < end)
		temp = temp->next;
	trian->vert[1] = temp->ver;
	free(sp);
	sp = ft_split(fl[2], '/');
	end = ft_atoi(sp[0]) - 1;
	temp = *ver;
	c = -1;
	while (++c < end)
		temp = temp->next;
	trian->vert[2] = temp->ver;
	c = -1;
	trian->next = NULL;
	return (trian);
}
