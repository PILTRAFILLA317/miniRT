/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/20 21:14:33 by umartin-         ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (error_printer(1), 1);
	if (ft_strlen(av[1]) < 4)
		return (error_printer(2), 1);
	if (av[1][ft_strlen(av[1]) - 1] != 't' || av[1][ft_strlen(av[1]) - 2] != 'r'
		|| av[1][ft_strlen(av[1]) - 3] != '.')
		return (error_printer(2), 1);
	return (0);
}
