/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:42:05 by becastro          #+#    #+#             */
/*   Updated: 2023/03/23 18:28:16 by becastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_filelen(char *path)
{
	int		fd;
	int		len;
	char	buff;

	fd = open(path, O_RDONLY);
	len = 0;
	if (fd < 1)
		return (0);
	while (read(fd, &buff, 1))
		len++;
	return (len);
}
