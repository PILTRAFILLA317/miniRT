/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/28 19:18:32 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	error_printer(int i)
{
	printf(BHRED "Error: " CLOSE);
	if (i == 1)
		printf(RED "Invalid number of scenes\n" CLOSE);
	if (i == 2)
		printf(RED "Invalid scene name\n" CLOSE);
	if (i == 3)
		printf(RED "Invalid scene\n" CLOSE);
	if (i == 4)
		printf(RED "Scene does not exist\n" CLOSE);
}

char	*first_char_trimmer(char *str)
{
	int		i;
	int		c;
	char	*rtn;

	i = 0;
	c = 0;
	rtn = ft_calloc(sizeof(char *), (ft_strlen(str) - 1));
	while (++i < ((int)ft_strlen(str)))
	{
		rtn[c] = str[i];
		c++;
	}
	rtn[c] = 0;
	free(str);
	return (rtn);
}

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

int	elem_type(char *line, t_elem *elem)
{
	char	**fl;

	if (line[ft_strlen(line) - 1] == '\n')
		line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (line[0] == 'L')
	{
		if (ft_doublestrlen(fl) != 4 || light_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_light(elem, light_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 'p' && line[1] == 'l')
	{
		if (ft_doublestrlen(fl) < 4
			|| ft_doublestrlen(fl) > 5
			|| plane_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_plane(elem, plane_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 's' && line[1] == 'p')
	{
		if (ft_doublestrlen(fl) < 4
			|| ft_doublestrlen(fl) > 5
			|| sphere_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_sphere(elem, sphere_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 'c' && line[1] == 'y')
	{
		if (ft_doublestrlen(fl) != 6 || cyl_pre_chkr(fl))
			return (error_printer(3), 1);
		if (new_cyl(elem, cyl_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else if (line[0] == 't')
	{
		// if (ft_doublestrlen(fl) != 4)
		// 	return (error_printer(3), 1);
		if (new_triangle(elem, triangle_creator(fl, elem)))
			return (error_printer(3), 1);
	}
	else
		return (error_printer(3), 1);
	return (0);
}

void	id_creator(t_elem *elem)
{
	int			id;
	t_sphere	*s_head;
	t_cyl		*c_head;
	t_plane		*p_head;

	s_head = elem->sphere;
	c_head = elem->cyl;
	p_head = elem->pl;
	id = 0;
	while (s_head != NULL)
	{
		s_head->id = id;
		id++;
		s_head = s_head->next;
	}
	id = 0;
	while (c_head != NULL)
	{
		c_head->id = id;
		c_head->bot_disc.id = id;
		c_head->top_disc.id = id;
		id++;
		c_head = c_head->next;
	}
	id = 0;
	while (p_head != NULL)
	{
		p_head->id = id;
		id++;
		p_head = p_head->next;
	}
}

int	ft_close(t_elem *elem)
{
	mlx_destroy_window(elem->mlx, elem->win);
	exit(0);
	return (0);
}

int	ft_keypress(int keycode, t_elem *elem)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(elem->mlx, elem->win);
		exit(0);
	}
	if (keycode == 2)
	{
		mlx_clear_window(elem->mlx, elem->win);
		elem->cam.orient.x += 0.1;
		elem->cam.orient = vec_norm(elem->cam.orient);
		ray_caster(elem);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		file;
	char	*line;
	t_elem	elem;

	if (ac != 2 || WIN_X < 1 || WIN_Y < 1)
		return (error_printer(1), 1);
	if (access(av[1], F_OK))
		return (error_printer(4), 1);
	ft_memset(&elem, 0, sizeof(elem));
	elem.light = NULL;
	if (ft_strlen(av[1]) < 4)
		return (error_printer(2), 1);
	if (av[1][ft_strlen(av[1]) - 1] != 't' || av[1][ft_strlen(av[1]) - 2] != 'r'
		|| av[1][ft_strlen(av[1]) - 3] != '.')
		return (error_printer(2), 1);
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	if (first_line_alight(line, &elem) == -1)
		return (error_printer(3), 1);
	line = get_next_line(file);
	if (second_line_cam(last_char_trimmer(line), &elem) == -1)
		return (error_printer(3), 1);
	while (line != NULL)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		if (elem_type(line, &elem))
			return (1);
	}
	id_creator(&elem);
	elem.mlx = mlx_init();
	elem.win = mlx_new_window(elem.mlx, WIN_X, WIN_Y, "miniRT");
	mlx_hook(elem.win, 2, 1L << 0, ft_keypress, &elem);
	mlx_hook(elem.win, 17, 1L << 17, ft_close, &elem);
	ray_caster(&elem);
	mlx_loop(elem.mlx);
	return (0);
}
