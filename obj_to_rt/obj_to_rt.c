/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:47:43 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/17 19:21:43 by umartin-         ###   ########.fr       */
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

void	vec_printer(t_vec	vec, int fd)
{
	write(fd, vec.x, ft_strlen(vec.x));
	write(fd, ",", 1);
	write(fd, vec.y, ft_strlen(vec.y));
	write(fd, ",", 1);
	write(fd, vec.z, ft_strlen(vec.z));
}

int	new_trian(t_ver **trian, t_ver *new)
{
	t_ver	*tmp;

	if (!(*trian))
	{
		*trian = new;
		return (0);
	}
	tmp = *trian;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	new_face(t_tri **trian, t_tri *new)
{
	t_tri	*tmp;

	if (!(*trian))
	{
		*trian = new;
		return (0);
	}
	tmp = *trian;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int	new_norm(t_norm **norm, t_norm *new)
{
	t_norm	*tmp;

	if (!(*norm))
	{
		*norm = new;
		return (0);
	}
	tmp = *norm;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

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

int	main(int ac, char **av)
{
	int		file;
	int		fd;
	char	*line;
	t_ver	*vertice;
	t_norm	*normal;
	t_tri	*tri;

	(void)ac;
	ft_memset(&vertice, 0, sizeof(vertice));
	ft_memset(&normal, 0, sizeof(normal));
	ft_memset(&tri, 0, sizeof(tri));
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	if (line == NULL)
		exit (0);
	lister(&vertice, &normal, &tri, last_char_trimmer(line));
	while (line != NULL)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		lister(&vertice, &normal, &tri, last_char_trimmer(line));
	}
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
	return (0);
}
