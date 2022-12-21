/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/21 21:06:31 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_printer(int i)
{
	printf(BHRED"Error: "CLOSE);
	if (i == 1)
		printf(RED"Invalid number of scenes\n"CLOSE);
	if (i == 2)
		printf(RED"Invalid scene name\n"CLOSE);
	if (i == 3)
		printf(RED"Invalid scene\n"CLOSE);
}

char	*first_char_trimmer(char	*str)
{
	int		i;
	int		c;
	char	*rtn;

	i = 0;
	c = 0;
	rtn = ft_calloc(sizeof(char *), (ft_strlen(str) - 2));
	while (++i < ((int)ft_strlen(str)))
	{
		rtn[c] = str[i];
		c++;
	}
	free(str);
	return (rtn);
}

char	*last_char_trimmer(char	*str)
{
	int		i;
	int		c;
	char	*rtn;

	i = -1;
	c = 0;
	rtn = ft_calloc(sizeof(char *), (ft_strlen(str) - 2));
	while (++i < ((int)ft_strlen(str) - 1))
	{
		rtn[c] = str[i];
		c++;
	}
	free(str);
	return (rtn);
}

int	first_line(char *line, t_elem *elem)
{
	char	**fl;
	char	**rgb;

	line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (fl[0][0] != 'A' || ft_doublestrlen(fl) != 3)
		return (error_printer(3), 1);
	elem->alight.ratio = ft_strtod(fl[1]);
	rgb = ft_split(fl[2], ',');
	elem->alight.r = ft_atoi(rgb[0]);
	elem->alight.g = ft_atoi(rgb[1]);
	elem->alight.b = ft_atoi(rgb[2]);
	return (0);
}

int	main(int ac, char **av)
{
	int		file;
	char	*line;
	t_elem	elem;

	if (ac != 2)
		return (error_printer(1), 1);
	if (ft_strlen(av[1]) < 4)
		return (error_printer(2), 1);
	if (av[1][ft_strlen(av[1]) - 1] != 't' || av[1][ft_strlen(av[1]) - 2] != 'r'
		|| av[1][ft_strlen(av[1]) - 3] != '.')
		return (error_printer(2), 1);
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	first_line(line, &elem);
	printf("RATIO = %f\n", elem.alight.ratio);
	printf("R = %d\n", elem.alight.r);
	printf("G = %d\n", elem.alight.g);
	printf("B = %d\n", elem.alight.b);
	return (0);
}
