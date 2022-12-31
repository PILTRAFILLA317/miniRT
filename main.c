/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/31 17:07:23 by umartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void error_printer(int i)
{
	printf(BHRED "Error: " CLOSE);
	if (i == 1)
		printf(RED "Invalid number of scenes\n" CLOSE);
	if (i == 2)
		printf(RED "Invalid scene name\n" CLOSE);
	if (i == 3)
		printf(RED "Invalid scene\n" CLOSE);
}

char *first_char_trimmer(char *str)
{
	int i;
	int c;
	char *rtn;

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

char *last_char_trimmer(char *str)
{
	int i;
	int c;
	char *rtn;

	i = -1;
	c = 0;
	rtn = ft_calloc(sizeof(char *), (ft_strlen(str) - 1));
	while (++i < ((int)ft_strlen(str) - 1))
	{
		rtn[c] = str[i];
		c++;
	}
	rtn[c] = 0;
	free(str);
	return (rtn);
}

int elem_type(char *line, t_elem *elem)
{
	char	**fl;

	line = last_char_trimmer(line);
	fl = ft_split(line, ' ');
	if (line[0] == 'L')
	{
		if (ft_doublestrlen(fl) != 4)
			return (error_printer(3), 1);
		new_light(&elem->light, light_creator(fl));
	}
	if (line[0] == 'p' && line[1] == 'l')
	{
		if (ft_doublestrlen(fl) != 4)
			return (error_printer(3), 1);
		new_plane(&elem->light, plane_creator(fl));
	}
	if (line[0] == 's' && line[1] == 'p')
	{
		if (ft_doublestrlen(fl) != 4)
			return (error_printer(3), 1);
		new_sphere(&elem->light, sphere_creator(fl));
	}
	if (line[0] == 'c' && line[1] == 'y')
	{
		if (ft_doublestrlen(fl) != 4)
			return (error_printer(3), 1);
		new_cyl(&elem->light, cyl_creator(fl));
	}
	return (0);
}

void printer(t_elem elem)
{
	printf("\n////////////AMBIENT LIGHT////////////\n");
	printf("AL-RATIO = %f\n", elem.alight.ratio);
	printf("AL-R = %d\n", elem.alight.r);
	printf("AL-G = %d\n", elem.alight.g);
	printf("AL-B = %d\n", elem.alight.b);
	printf("\n////////////CAM////////////\n");
	printf("CAM-FOV = %d\n", elem.cam.fov);
	printf("CAM-POS-X = %f\n", elem.cam.pos.x);
	printf("CAM-POS-Y = %f\n", elem.cam.pos.y);
	printf("CAM-POS-Z = %f\n", elem.cam.pos.z);
	printf("CAM-ROT-X = %f\n", elem.cam.orient.x);
	printf("CAM-ROT-Y = %f\n", elem.cam.orient.y);
	printf("CAM-ROT-Z = %f\n", elem.cam.orient.z);
	while (elem.light != NULL)
	{
		printf("\n////////////LIGHT////////////\n");
		printf("LIGHT-BR = %f\n", elem.light->bright);
		printf("LIGHT-POS-X = %f\n", elem.light->pos.x);
		printf("LIGHT-POS-Y = %f\n", elem.light->pos.y);
		printf("LIGHT-POS-Z = %f\n", elem.light->pos.z);
		printf("LIGHT-R = %d\n", elem.light->r);
		printf("LIGHT-G = %d\n", elem.light->g);
		printf("LIGHT-B = %d\n", elem.light->b);
		elem.light = elem.light->next;
	}
}

int main(int ac, char **av)
{
	int		file;
	char	*line;
	t_elem	elem;

	ft_memset(&elem, 0, sizeof(elem));
	elem.light = NULL;
	if (ac != 2)
		return (error_printer(1), 1);
	if (ft_strlen(av[1]) < 4)
		return (error_printer(2), 1);
	if (av[1][ft_strlen(av[1]) - 1] != 't' || av[1][ft_strlen(av[1]) - 2] != 'r'
		|| av[1][ft_strlen(av[1]) - 3] != '.')
		return (error_printer(2), 1);
	file = open(av[1], O_RDONLY);
	line = get_next_line(file);
	if (first_line_alight(line, &elem) == -1)
		return (error_printer(3), 1);
	line = get_next_line(file);
	if (second_line_cam(line, &elem) == -1)
		return (error_printer(3), 1);
	while (line != NULL)
	{
		line = get_next_line(file);
		if (line == NULL)
			break ;
		elem_type(line, &elem);
	}
	printer(elem);
	return (0);
}
