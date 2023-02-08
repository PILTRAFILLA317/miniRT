/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:23:26 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/08 21:06:28 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/obj_to_rt.h"

static int	ft_get_digits(long n)
{
	size_t	digits;
	int		neg;

	digits = 0;
	neg = 0;
	if (n < 0)
	{
		digits++;
		neg++;
		n = -n;
	}
	while (n >= 1)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static char	*ft_strgen(char *dest, long nbr, int len, int neg)
{
	if (nbr != 0)
		dest = malloc(sizeof(char) * (len + 1));
	else
		return (dest = ft_strdup("0"));
	if (!dest)
		return (0);
	neg = 0;
	if (nbr < 0)
	{
		neg++;
		nbr = -nbr;
	}
	dest[len] = '\0';
	while (--len)
	{
		dest[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (neg >= 1)
		dest[0] = '-';
	else
		dest[0] = (nbr % 10) + '0';
	return (dest);
}

char	*ft_dotoa(double n)
{
	int		len;
	long	nbr;
	int		neg;
	char	*result;

	nbr = n;
	len = ft_get_digits(nbr);
	neg = 0;
	result = 0;
	result = ft_strgen(result, nbr, len, neg);
	if (!result)
		return (0);
	return (result);
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