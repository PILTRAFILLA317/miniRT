/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:38:27 by umartin-          #+#    #+#             */
/*   Updated: 2023/01/17 18:23:30 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define KEY_ESC 53
# define WIN_X 1920.0
# define WIN_Y 1080.0

# define BUFFER_SIZE 1

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

typedef struct s_rotmtx
{
	t_vec	pos;
	t_vec	rot;
}	t_rotmtx;

typedef struct s_light
{
	t_vec			pos;
	int				r;
	int				g;
	int				b;
	double			bright;
	struct s_light	*next;
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
	struct s_rotmtx	mtx;
	struct s_vec	pos;
	struct s_vec	orient;
	int				fov;
}	t_cam;

typedef struct s_sphere
{
	struct s_vec	pos;
	double			diam;
	int				x;
	int				r;
	int				g;
	int				b;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	struct s_vec	pos;
	struct s_vec	orient;
	int				x;
	int				r;
	int				g;
	int				b;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cyl
{
	struct s_vec	pos;
	struct s_vec	orient;
	double			diam;
	int				x;
	double			h;
	int				r;
	int				g;
	int				b;
	struct s_cyl	*prev;
	struct s_cyl	*next;
}	t_cyl;

typedef struct s_elem
{
	void		*mlx;
	void		*win;
	t_alight	alight;
	t_cam		cam;
	t_light		*light;
	t_sphere	*sphere;
	t_cyl		*cyl;
	t_plane		*pl;
}	t_elem;

////////// UTILS //////////
double		ft_strtod(char *str);
char		*first_char_trimmer(char	*str);
char		*last_char_trimmer(char	*str);
void		error_printer(int i);
int			digit_checker(char *str);

////////// AL_CAM_INIT //////////
int			first_line_alight(char *line, t_elem *elem);
int			second_line_cam(char *line, t_elem *elem);

////////// LIGHT_LNKD //////////
t_light		*light_creator(char **fl, t_elem *e);
void		new_light(t_light **lst, t_light *new);
int			light_checker(t_elem *elem);
int			light_pre_chkr(char **fl);

////////// PLANE_LNKD //////////
t_plane		*plane_creator(char **fl, t_elem *e);
void		new_plane(t_plane **lst, t_plane *new);
int			plane_checker(t_elem *elem);
int			plane_pre_chkr(char **fl);

////////// SPHERE_LNKD //////////
void		new_sphere(t_sphere **lst, t_sphere *new);
t_sphere	*sphere_creator(char **fl, t_elem *e);
void		sphere_light(t_sphere **lst, t_sphere *new);
int			sphere_checker(t_elem *elem);
int			sphere_pre_chkr(char **fl);

////////// CYL_LNKD //////////
t_cyl		*cyl_creator(char **fl, t_elem *e);
void		new_cyl(t_cyl **lst, t_cyl *new);
int			cyl_checker(t_elem *elem);
int			cyl_pre_chkr(char **fl);

////////// VEC_UTILS //////////
double		vec_dot(t_vec a, t_vec b);
double		vec_len(t_vec vec);
t_vec		vec_norm(t_vec vec);
t_vec		points_to_vec(t_vec a, t_vec b);

void		ray_caster(t_elem *elem);

#endif
