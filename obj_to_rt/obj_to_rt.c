/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:47:43 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/08 21:25:29 by umartin-         ###   ########.fr       */
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

int	new_trian(t_tri **trian, t_tri *new)
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

t_tri	*trian_creator(char **fl)
{
	t_tri	*trian;

	trian = malloc(sizeof(t_tri));
	trian->tri.x = last_char_trimmer(fl[1]);
	trian->tri.y = last_char_trimmer(fl[2]);
	trian->tri.z = last_char_trimmer(fl[3]);
	trian->next = NULL;
	return (trian);
}

t_norm	*norm_creator(char **fl)
{
	t_norm	*trian;

	trian = malloc(sizeof(t_tri));
	trian->norm.x = last_char_trimmer(fl[1]);
	trian->norm.y = last_char_trimmer(fl[2]);
	trian->norm.z = last_char_trimmer(fl[3]);
	trian->next = NULL;
	return (trian);
}

void	lister(t_tri **trian, t_norm **normal, char *line)
{
	char	**fl;

	fl = ft_split(line, ' ');
	if (!line)
		return ;
	if (line[0] == 'v' && line[1] == ' ')
		new_trian(trian, trian_creator(fl));
	else if (line[0] == 'v' && line[1] == 'n')
		new_norm(normal, norm_creator(fl));
}

int	main(int ac, char **av)
{
	int		file;
	int		fd;
	char	*line;
	t_tri	*trian;
	t_norm	*normal;

	(void)ac;
	ft_memset(&trian, 0, sizeof(trian));
	ft_memset(&normal, 0, sizeof(normal));
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	lister(&trian, &normal, line);
	while (line != NULL)
	{
		line = get_next_line(file);
		lister(&trian, &normal, line);
	}
	fd = open(av[2], O_CREAT | O_RDWR
			| O_TRUNC | O_APPEND, 0644);
	while (trian != NULL)
	{
		write(fd, "t ", 2);
		vec_printer(trian->tri, fd);
		write (fd, " ", 1);
		vec_printer(normal->norm, fd);
		write (fd, " ", 1);
		if (av[3])
		{
			write(fd, av[3], ft_strlen(av[3]));
			write(fd, "\n", 1);
		}
		else
			write(fd, "255,255,255\n", 12);
		trian = trian->next;
	}
	while (normal != NULL)
	{
		normal = normal->next;
	}
	return (0);
}