/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:03:52 by becastro          #+#    #+#             */
/*   Updated: 2023/03/09 20:20:21 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

void	trian_lister(char **fl, t_tri **tri, t_ver **ver)
{
	char	**t;
	int		e;

	e = ft_doublestrlen(fl) - 1;
	while (e - 1 > 1)
	{
		t = malloc(sizeof(char *) * 4);
		t[0] = ft_strdup(fl[1]);
		t[1] = ft_strdup(fl[e]);
		t[2] = ft_strdup(fl[e - 1]);
		t[3] = NULL;
		new_face(tri, face_creator(t, ver));
		ft_doublefree(t);
		e--;
	}
	ft_doublefree(fl);
}

void	lister(t_ver **ver, t_tri **tri, char *line)
{
	char	**fl;

	if (!line)
		return ;
	fl = ft_split(line, ' ');
	if (line[0] == 'v' && line[1] == ' ')
		new_trian(ver, trian_creator(fl));
	else if (line[0] == 'f')
		trian_lister(fl, tri, ver);
	else
		ft_doublefree(fl);
	free(line);
}
