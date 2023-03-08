/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:03:52 by becastro          #+#    #+#             */
/*   Updated: 2023/03/07 16:16:16 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

void	trian_lister(char **fl, t_tri **tri, t_ver **ver)
{
	char	**t;
	int		i;
	int		e;

	i = -1;
	t = malloc(sizeof(char *) * 4);
	t[3] = NULL;
	if (ft_doublestrlen(fl) == 4)
	{
		t[0] = fl[1];
		t[1] = fl[2];
		t[2] = fl[3];
		new_face(tri, face_creator(t, ver));
		return ;
	}
	e = ft_doublestrlen(fl) - 1;
	while (e - 1 > 1)
	{
		t[0] = fl[1];
		t[1] = fl[e];
		t[2] = fl[e - 1];
		new_face(tri, face_creator(t, ver));
		e--;
	}
}

void	lister(t_ver **ver, t_norm **normal, t_tri **tri, char *line)
{
	char	**fl;

	if (!line)
		return ;
	fl = ft_split(line, ' ');
	if (line[0] == 'v' && line[1] == ' ')
		new_trian(ver, trian_creator(fl));
	else if (line[0] == 'v' && line[1] == 'n')
		new_norm(normal, norm_creator(fl));
	else if (line[0] == 'f')
		trian_lister(fl, tri, ver);
}
