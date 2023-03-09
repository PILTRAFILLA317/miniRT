/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:47:43 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/09 20:19:36 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

char	*last_char_trimmer(char *str)
{
	int		i;
	int		c;
	char	*rtn;

	i = -1;
	c = 0;
	rtn = ft_calloc(sizeof(char *), (ft_strlen(str) - 1));
	while (++i < ((int)ft_strlen(str) - 1))
	{
		rtn[c] = str[i];
		c++;
	}
	rtn[c] = 0;
	free(str);
	return (rtn);
}

void	vec_printer(t_vec vec, int fd)
{
	write(fd, vec.x, ft_strlen(vec.x));
	write(fd, ",", 1);
	write(fd, vec.y, ft_strlen(vec.y));
	write(fd, ",", 1);
	write(fd, vec.z, ft_strlen(vec.z));
}

void	writter(t_tri *tri, char **av)
{
	int	fd;

	fd = open(av[2], O_CREAT | O_RDWR
			| O_TRUNC | O_APPEND, 0644);
	while (tri != NULL)
	{
		write(fd, "t ", 2);
		vec_printer(tri->vert[0], fd);
		write (fd, "|", 1);
		vec_printer(tri->vert[1], fd);
		write (fd, "|", 1);
		vec_printer(tri->vert[2], fd);
		write (fd, " ", 1);
		if (av[3])
		{
			write(fd, av[3], ft_strlen(av[3]));
			write(fd, "\n", 1);
		}
		else
			write(fd, "255,255,255\n", 12);
		tri = tri->next;
	}
}

void	freedom(t_ver *ver, t_tri *tri)
{
	t_ver	*vertmp;
	t_tri	*tritmp;

	while (ver)
	{
		vertmp = ver;
		ver = ver->next;
		free(vertmp->ver.x);
		free(vertmp->ver.y);
		free(vertmp->ver.z);
		free (vertmp);
	}
	while (tri)
	{
		tritmp = tri;
		tri = tri->next;
		free (tritmp);
	}
	free (ver);
	free (tri);
}

int	main(int ac, char **av)
{
	int		file;
	char	*line;
	t_ver	*vertice;
	t_tri	*tri;

	(void)ac;
	ft_memset(&vertice, 0, sizeof(vertice));
	ft_memset(&tri, 0, sizeof(tri));
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	if (line == NULL)
		exit (0);
	lister(&vertice, &tri, last_char_trimmer(line));
	while (line != NULL)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		lister(&vertice, &tri, last_char_trimmer(line));
	}
	return (writter(tri, av), freedom(vertice, tri), 0);
}
