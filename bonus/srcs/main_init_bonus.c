/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:11:26 by becastro          #+#    #+#             */
/*   Updated: 2023/03/20 18:06:06 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

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
	return (0);
}

int	arg_error_checker(int ac, char **av)
{
	if (ac != 2 || WIN_X < 1 || WIN_Y < 1)
		return (error_printer(1), 1);
	if (access(av[1], F_OK))
		return (error_printer(4), 1);
	if (ft_strlen(av[1]) < 4)
		return (error_printer(2), 1);
	if (av[1][ft_strlen(av[1]) - 1] != 't' || av[1][ft_strlen(av[1]) - 2] != 'r'
		|| av[1][ft_strlen(av[1]) - 3] != '.')
		return (error_printer(2), 1);
	return (0);
}

int	file_error_checker(t_elem *elem, char *line, int file)
{
	while (line && line[0] == '\n')
		line = get_next_line(file);
	if (first_line_alight(line, elem) == -1)
		return (error_printer(3), 1);
	line = get_next_line(file);
	while (line && line[0] == '\n')
		line = get_next_line(file);
	if (second_line_cam(last_char_trimmer(line), elem) == -1)
		return (error_printer(3), 1);
	return (0);
}

void	main_init(t_elem *elem)
{
	id_creator(elem);
	elem->mlx = mlx_init();
	elem->win = mlx_new_window(elem->mlx, WIN_X, WIN_Y, "miniRT");
	mlx_hook(elem->win, 2, 1L << 0, ft_keypress, elem);
	mlx_hook(elem->win, 17, 1L << 17, ft_close, elem);
	ray_caster(elem);
	mlx_loop(elem->mlx);
}
