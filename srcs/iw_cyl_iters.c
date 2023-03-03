
#include "../includes/minirt.h"

int	i_w_shead_iter(t_dirpos *arg, t_sphere *s_head, t_light *light)
{
	if (sph_intersect(arg->pos, s_head, arg->dir) == 1)
		if (vec_len(vec_diff(arg->pos,
					sph_intersect_point(arg->pos, s_head, arg->dir)))
			< vec_len(vec_diff(arg->pos, light->pos)))
			return (1);
	return (0);
}

int	i_w_chead_iter(t_dirpos *arg, t_cyl *c_head, t_cyl *cyl, t_light *light)
{
	if (cyl_intersect(arg->pos, c_head, arg->dir) == 1
		&& c_head->id != cyl->id)
		if (vec_len(vec_diff(arg->pos,
					cyl_intersect_point(arg->pos, c_head, arg->dir)))
			< vec_len(vec_diff(arg->pos, light->pos)))
			return (1);
	if (disc_intersect(arg->pos, &c_head->bot_disc, arg->dir) == 1
		&& c_head->id != cyl->id)
		if (vec_len(vec_diff(arg->pos, disc_intersect_point(arg->pos,
						&c_head->bot_disc, arg->dir)))
			< vec_len(vec_diff(arg->pos, light->pos)))
			return (1);
	if (disc_intersect(arg->pos, &c_head->top_disc, arg->dir) == 1
		&& c_head->id != cyl->id)
		if (vec_len(vec_diff(arg->pos, disc_intersect_point(arg->pos,
						&c_head->top_disc, arg->dir)))
			< vec_len(vec_diff(arg->pos, light->pos)))
			return (1);
	return (0);
}
