/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becastro <becastro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:38:27 by umartin-          #+#    #+#             */
/*   Updated: 2023/03/06 13:47:22 by becastro         ###   ########.fr       */
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
# include <pthread.h>
# include <math.h>

# define KEY_ESC 53
# define WIN_X 1920.0
# define WIN_Y 1080.0

# define BUFFER_SIZE	1
# define NUM_THREAD		12
# define MAX_MIRR_RAYS	100

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

enum e_type {p, s, c, d, t, n};

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

typedef struct s_dirpos
{
	t_vec	pos;
	t_vec	dir;
}	t_dirpos;

typedef struct s_light
{
	t_vec			pos;
	t_vec			color;
	double			bright;
	struct s_light	*next;
}	t_light;

typedef struct s_alight
{
	double	ratio;
	t_vec	color;
}	t_alight;

typedef struct s_cam
{
	struct s_rotmtx	mtx;
	struct s_vec	pos;
	struct s_vec	right;
	struct s_vec	up;
	struct s_vec	forward;
	struct s_vec	orient;
	double			fov;
	double			h;
	double			w;
	double			theta;
	double			a_ratio;
}	t_cam;

typedef struct s_sphere
{
	struct s_vec	pos;
	struct s_vec	color;
	double			diam;
	double			ref;
	int				x;
	int				id;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	struct s_vec	pos;
	struct s_vec	orient;
	struct s_vec	color;
	double			ref;
	int				x;
	int				id;
	struct s_plane	*next;
}	t_plane;

typedef struct s_tri
{
	struct s_vec	ver[3];
	struct s_vec	orient;
	struct s_vec	color;
	int				id;
	struct s_tri	*next;
}	t_tri;

typedef struct s_disc
{
	struct s_vec	pos;
	struct s_vec	orient;
	struct s_vec	color;
	double			diam;
	int				id;
}	t_disc;

typedef struct s_cyl
{
	struct s_vec	pos;
	struct s_vec	pos2;
	struct s_vec	orient;
	struct s_vec	orient2;
	struct s_vec	color;
	t_disc			bot_disc;
	t_disc			top_disc;
	double			diam;
	double			h;
	int				id;
	struct s_cyl	*next;
}	t_cyl;

typedef struct s_th
{
	pthread_t		th;
	int				core;
	struct s_elem	*elem;
}	t_th;

typedef struct s_elem
{
	pthread_mutex_t	pixl;
	t_th			*th;
	void			*mlx;
	void			*win;
	t_alight		alight;
	t_cam			cam;
	t_light			*light;
	t_sphere		*sphere;
	t_cyl			*cyl;
	t_plane			*pl;
	t_tri			*t;
}	t_elem;

typedef struct s_object
{
	enum e_type	type;
	void		*elem;
}	t_object;

typedef struct s_objlen
{
	t_object	obj;
	double		len;
}	t_objlen;

////////// UTILS //////////
double		ft_strtod(char *str);
char		*first_char_trimmer(char	*str);
char		*last_char_trimmer(char	*str);
void		error_printer(int i);
int			digit_checker(char *str);
double		num_to_pos(double num);

////////// AL_CAM_INIT //////////
int			first_line_alight(char *line, t_elem *elem);
int			second_line_cam(char *line, t_elem *elem);
void		init_elem_orient(t_elem *elem, char **rot, char **fl);
void		init_elem_cam(t_elem *elem, char **pos);

////////// LIGHT_LNKD //////////
t_light		*light_creator(char **fl, t_elem *e);
int			new_light(t_elem *elem, t_light *new);
int			light_pre_chkr(char **fl);

////////// PLANE_LNKD //////////
t_plane		*plane_creator(char **fl, t_elem *e);
int			new_plane(t_elem *elem, t_plane *new);
int			plane_pre_chkr(char **fl);

////////// SPHERE_LNKD //////////
int			new_sphere(t_elem *elem, t_sphere *new);
t_sphere	*sphere_creator(char **fl, t_elem *e);
void		sphere_light(t_sphere **lst, t_sphere *new);
int			sphere_pre_chkr(char **fl);

////////// CYL_LNKD //////////
int			new_cyl(t_elem *elem, t_cyl *new);
t_cyl		*cyl_creator(char **fl, t_elem *e);
int			cyl_pre_chkr(char **fl);

////////// TRI_LNKD //////////
t_tri		*triangle_creator(char **fl, t_elem *e);
int			new_triangle(t_elem *elem, t_tri *new);

////////// VEC_UTILS //////////
double		vec_dot(t_vec a, t_vec b);
double		vec_len(t_vec vec);
t_vec		vec_norm(t_vec vec);
t_vec		points_to_vec(t_vec a, t_vec b);
double		vec_selfdot(t_vec a);
t_vec		vec_diff(t_vec a, t_vec b);
t_vec		vec_point(t_vec dir, t_vec pos, double t);
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_mult(t_vec vec, double a);
void		vec_printer(t_vec	vec);
t_vec		vec_div(t_vec vec, double a);
t_vec		new_vec(double x, double y, double z);
t_vec		vec_mult_vec(t_vec a, t_vec b);
t_vec		vec_clamp(double min, double max, t_vec value);
t_vec		vec_unit(t_vec vec);
t_vec		vec_cross(t_vec v, t_vec w);

////////// COLOR_UTILS //////////
int			convert_rgb(t_vec col);
t_vec		col_to_255(t_vec	col);
t_vec		col_to_01(t_vec	col);
double		clamp(double min, double max, double value);
t_vec		double_to_rgb(int num);

////////// INTERSECTIONS //////////
int			cyl_intersect(t_vec pos, t_cyl *cyl, t_vec dir);
t_vec		cyl_intersect_point(t_vec pos, t_cyl *cyl, t_vec dir);
int			disc_intersect(t_vec pos, t_disc *disc, t_vec dir);
t_vec		disc_intersect_point(t_vec pos, t_disc *disc, t_vec dir);
t_vec		pl_intersect_point(t_vec pos, t_plane *pl, t_vec dir);
int			pl_intersect(t_vec pos, t_plane *pl, t_vec dir);
t_vec		sph_intersect_point(t_vec pos, t_sphere *sph, t_vec dir);
int			sph_intersect(t_vec pos, t_sphere *sph, t_vec dir);
int			tri_intersect(t_vec pos, t_tri *tri, t_vec dir);
t_vec		t_intersect_point(t_vec pos, t_tri *tri, t_vec dir);
int			iw_sph_s_it(t_elem *elem,
				t_dirpos arg, t_sphere sph, t_light light);
int			iw_sph_c_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_sph_p_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_sph_t_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_cyl_s_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_cyl_c_it(t_elem *elem,
				t_dirpos arg, t_cyl cyl, t_light light);
int			iw_cyl_p_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_cyl_t_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_pl_s_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_pl_c_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_pl_p_it(t_elem *elem, t_dirpos arg, t_plane pl, t_light light);
int			iw_pl_t_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_disc_s_it(t_elem *elem, t_dirpos arg, t_light light);
int			iw_disc_c_it(t_elem *elem,
				t_dirpos arg, t_disc disc, t_light light);

////////// MIRRORS //////////
int			sph_mirror(t_elem *elem, t_dirpos rt, t_sphere sph, int *ray);
int			pl_mirror(t_elem *elem, t_dirpos rt, t_plane pl, int *ray);
int			pl_checkboard(t_elem *elem, t_dirpos rt, t_plane pl, int *ray);

////////// RAY_CAST //////////
void		ray_caster(t_elem *elem);
t_vec		light_comb_sph(t_sphere sph, t_elem *elem, t_vec rtn);
t_vec		light_comb_pl(t_plane pl, t_elem *elem, t_vec rtn);
t_vec		light_comb_cyl(t_cyl cyl, t_elem *elem, t_vec rtn);
t_vec		light_comb_disc(t_disc disc, t_elem *elem, t_vec rtn);
t_vec		light_comb_tri(t_tri tri, t_elem *elem, t_vec rtn);
t_vec		mid_point(t_cyl cyl, t_vec inter);
int			i_w_sph(t_elem *elem, t_dirpos arg, t_sphere sph, t_light light);
int			i_w_cyl(t_elem *elem, t_dirpos arg, t_cyl cyl, t_light light);
int			i_w_pl(t_elem *elem, t_dirpos arg, t_plane pl, t_light light);
int			i_w_disc(t_elem *elem, t_dirpos arg, t_disc disc, t_light light);
int			i_w_tri(t_elem *elem, t_dirpos arg, t_tri tri, t_light light);
int			color(t_elem *elem, t_dirpos dp, t_object co, int *ray);

////////// FIRST_INTER //////////
t_objlen	pl_f_i(t_elem *elem, t_dirpos d, t_object co, t_objlen ol);
t_objlen	sph_f_i(t_elem *elem, t_dirpos d, t_object co, t_objlen ol);
t_objlen	tri_f_i(t_elem *elem, t_dirpos d, t_objlen ol);
t_objlen	cyl_f_i(t_elem *elem, t_dirpos d, t_objlen ol);

////////// COLORS //////////
int			cyl_color(t_elem *elem, t_vec dir, t_vec pos, t_cyl cyl);
int			sph_color(t_elem *elem, t_dirpos d, t_sphere sph, int *ray);
int			disc_color(t_elem *elem, t_vec dir, t_vec pos, t_disc disc);
int			plane_color(t_elem *elem, t_dirpos d, t_plane pl, int *ray);
int			trian_color(t_elem *elem, t_vec dir, t_vec pos, t_tri tri);

#endif
