/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:22 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

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

int	main(int ac, char **av)
{
	int		file;
	char	*line;
	t_elem	elem;

	if (arg_error_checker(ac, av))
		return (1);
	ft_memset(&elem, 0, sizeof(elem));
	elem.light = NULL;
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	if (file_error_checker(&elem, line, file))
		return (1);
	while (line != NULL)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		if (line && line[0] == '\n')
			line = get_next_line(file);
		if (elem_type(line, &elem))
			return (1);
	}
	main_init(&elem);
	return (0);
}
