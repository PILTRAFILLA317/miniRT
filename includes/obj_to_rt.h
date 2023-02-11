/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_to_rt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:50:35 by umartin-          #+#    #+#             */
/*   Updated: 2023/02/11 16:35:43 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_TO_RT_H
# define OBJ_TO_RT_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define BUFFER_SIZE 1

typedef struct s_vec
{
	char	*x;
	char	*y;
	char	*z;
}	t_vec;

typedef struct s_tri
{
	t_vec			vert[3];
	struct s_tri	*next;
}	t_tri;

typedef struct s_ver
{
	t_vec			ver;
	struct s_ver	*next;
}	t_ver;

typedef struct s_norm
{
	t_vec			norm;
	struct s_norm	*next;
}	t_norm;

double	ft_strtod(char *str);

#endif
