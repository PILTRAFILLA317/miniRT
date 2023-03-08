/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:06:18 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/08 17:44:04 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

int	digit_checker(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return (1);
	while (str[++i])
	{
		if ((str[i] >= 48 && str[i] <= 57) || str[i] == 46 || str[i] == 45)
			continue ;
		else
			return (1);
	}
	return (0);
}

double	ft_strtod_double_creator(char **a, int s)
{
	double	rtn;
	double	res[2];
	int		i;

	i = -1;
	res[1] = 0;
	while (a[0][++i])
		res[1] = (a[0][i] - '0') + (res[1] * 10);
	i = -1;
	res[0] = 0;
	if (a[1] == NULL)
		return (rtn = res[1] * s, rtn);
	while (a[1][++i])
		res[0] = (a[1][i] - '0') + (res[0] * 10);
	while (i > 0)
	{
		res[0] = res[0] * 0.1;
		i--;
	}
	return (rtn = (res[1] + (res[0])) * s);
}

int	ft_strtod_chkr(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] < 46 || str[i] > 57)
			return (0);
		if (str[i] == 47)
			return (0);
		if (str[i] == 46)
			c++;
	}
	return (c);
}

double	ft_strtod(char *str)
{
	char	**a;
	int		c;
	int		s;

	if (str == NULL)
		return (0);
	c = 0;
	s = 1;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		str = first_char_trimmer(str);
	}
	c = ft_strtod_chkr(str);
	if (c > 1)
		return (0);
	a = ft_split(str, 46);
	ft_strtod_double_creator(a, s);
	return (ft_strtod_double_creator(a, s));
}
