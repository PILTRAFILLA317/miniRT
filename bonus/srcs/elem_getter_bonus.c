/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_getter_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:28:48 by becastro          #+#    #+#             */
/*   Updated: 2023/03/23 19:03:30 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

int	elem_type_uts(char *line, char **fl, t_elem *elem)
{
	if (line[0] == 'L')
		if (l_type(fl, elem))
			return (1);
	if (line[0] == 'p' && line[1] == 'l')
		if (pl_type(fl, elem))
			return (1);
	if (line[0] == 's' && line[1] == 'p')
		if (sp_type(fl, elem))
			return (1);
	if (line[0] == 'c' && line[1] == 'y')
		if (cy_type(fl, elem))
			return (1);
	if (line[0] == 't')
		if (t_type(fl, elem))
			return (1);
	return (0);
}

int	elem_type(char *line, t_elem *elem)
{
	char	**fl;

	if (line[ft_strlen(line) - 1] == '\n')
		line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (((line[0] == 'L' && line[1] == ' '))
		|| ((line[0] == 'p' && line[1] == 'l' && (line[2] == ' '
					|| ((line[2] == 'x' || line[2] == 'c') && line[3] == ' '))))
		|| ((line[0] == 's' && line[1] == 'p' && line[2] == ' '))
		|| ((line[0] == 'c' && line[1] == 'y' && line[2] == ' '))
		|| ((line[0] == 't') && line[1] == ' '))
	{
		if (elem_type_uts(line, fl, elem))
			return (1);
	}
	else
		return (error_printer(3), 1);
	return (0);
}
