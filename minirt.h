/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:38:27 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/21 21:24:42 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[0;33m"
# define BLUE 	"\033[0;34m"
# define PURPLE	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define BOLD	"\033[0;1m"
# define CLOSE	"\033[0;0m"
# define BHRED	"\e[1;91m"
# define BHGRN	"\e[1;92m"
# define BHBLK "\e[1;90m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ligth
{
	t_vec	pos;
	double	bright;
}	t_light;


typedef struct s_alight
{
	double	ratio;
	int		r;
	int		g;
	int		b;
}	t_alight;

typedef struct s_cam
{
	struct s_vec	pos;
	struct s_vec	orient;
	int				fov;
}	t_cam;

typedef struct s_sphere
{
	struct s_vec	pos;
	double			diam;
	int				r;
	int				g;
	int				b;
	struct t_sphere	*prev;
	struct t_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	struct s_vec	pos;
	struct s_vec	orient;
	int				r;
	int				g;
	int				b;
	struct t_plane	*prev;
	struct t_plane	*next;
}	t_plane;

typedef struct s_cyl
{
	struct s_vec	pos;
	struct s_vec	orient;
	double			diam;
	double			h;
	int				r;
	int				g;
	int				b;
	struct t_cyl	*prev;
	struct t_cyl	*next;
}	t_cyl;

typedef struct s_elem
{
	t_alight		alight;
	t_cam			cam;
	t_light			light;
	struct t_sph	*sphr;
	struct t_cyl	*cyl;
	struct t_pl		*pl;
	struct t_elem	*prev;
	struct t_elem	*next;
}	t_elem;

# define BUFFER_SIZE 1

double	ft_strtod(char *str);
char	*first_char_trimmer(char	*str);
char	*last_char_trimmer(char	*str);

#endif
