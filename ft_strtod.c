/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:06:18 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/27 15:52:05 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_strtod_double_creator(char **a, int s)
{
	double	rtn;
	int		res[2];
	int		i;

	i = -1;
	res[1] = 0;
	while (a[0][++i])
	{
		res[1] = (a[0][i] - '0') + (res[1] * 10);
		if (res[1] * s < -2147483648)
			return (0);
		if (res[1] * s > 2147483647)
			return (-1);
	}
	i = -1;
	res[0] = 0;
	if (a[1] == NULL)
		return (rtn = res[1] * s, rtn);
	while (a[1][++i])
	{
		res[0] = (a[1][i] - '0') + (res[0] * 10);
		if (res[0] * s < -2147483648 || res[0] * s > 2147483647)
			return (-1);
	}
	return (rtn = res[1] + (res[0] * 0.1));
}

int	ft_strtod_chkr(char *str)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if (str[i] < 46 || str[i] > 57 || str[i] == 47)
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
	if (ft_strtod_double_creator(a, s) == -1)
		return (0);
	return (ft_strtod_double_creator(a, s));
}
