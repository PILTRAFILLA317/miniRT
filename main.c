/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umartin- <umartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:36:06 by umartin-          #+#    #+#             */
/*   Updated: 2022/12/30 17:59:18 by umartin-         ###   ########.fr       */
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

// int	light_checker(t_elem *elem)
// {
// 	if (elem->light.bright < 0 || elem->light.bright > 1)
// 		return (-1);
// 	if (elem->light.r < 0 || elem->alight.r > 255)
// 		return (-1);
// 	if (elem->light.g < 0 || elem->alight.g > 255)
// 		return (-1);
// 	if (elem->light.b < 0 || elem->alight.r > 255)
// 		return (-1);
// 	return (0);
// }

// int	third_line_light(char *line, t_elem *elem)
// {
// 	char	**fl;
// 	char	**pos;
// 	char	**rgb;

// 	line = last_char_trimmer(line);
// 	fl = ft_split(line, ' ');
// 	if (fl[0][0] != 'L' || ft_doublestrlen(fl) != 4)
// 		return (error_printer(3), 1);
// 	pos = ft_split(fl[1], ',');
// 	elem->light.pos.x = ft_strtod(pos[0]);
// 	elem->light.pos.y = ft_strtod(pos[1]);
// 	elem->light.pos.z = ft_strtod(pos[2]);
// 	elem->light.bright = ft_strtod(fl[2]);
// 	rgb = ft_split(fl[3], ',');
// 	elem->light.r = ft_atoi(rgb[0]);
// 	elem->light.g = ft_atoi(rgb[1]);
// 	elem->light.b = ft_atoi(rgb[2]);
// 	if (light_checker(elem) == -1)
// 		return (-1);
// 	return (0);
// }

// int	elementType(char *line)
// {

// }

// int	createElements(char *filename)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open(filename, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (elementType(line))
// 			return (1);
// 		line = get_next_line(fd);
// 	}
// 	if (elementType(line))
// 		return (1);
// 	return (0);
// }

t_light	*light_creator(char **fl)
{
	char	**pos;
	char	**rgb;
	t_light	*light;

	light = malloc(sizeof(t_light));
	pos = ft_split(fl[1], ',');
	light->pos.x = ft_strtod(pos[0]);
	light->pos.y = ft_strtod(pos[1]);
	light->pos.z = ft_strtod(pos[2]);
	light->bright = ft_strtod(fl[2]);
	rgb = ft_split(fl[3], ',');
	light->r = ft_atoi(rgb[0]);
	light->g = ft_atoi(rgb[1]);
	light->b = ft_atoi(rgb[2]);
	light->next = NULL;
	return (light);
}

void	new_light(t_light **lst, t_light *new)
{
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next != NULL)
		(*lst) = (t_light *)(*lst)->next;
	(*lst)->next = (struct s_light *)new;
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
		elem.light = (t_light *)elem.light->next;
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
