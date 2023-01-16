/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:31:56 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 14:16:02 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdio.h>

static char	*fdf_get_file(char *input_path)
{
	int		input_fd;
	char	*file;
	char	*new;
	char	*input_line;

	input_fd = open(input_path, O_RDONLY);
	file = get_next_line(input_fd);
	if (!file)
		return (NULL);
	input_line = get_next_line(input_fd);
	while (input_line)
	{
		new = ft_strjoin(file, input_line);
		free(input_line);
		free(file);
		if (!new)
			return (NULL);
		file = new;
		input_line = get_next_line(input_fd);
	}
	return (file);
}

static int	fdf_map_get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	fdf_map_get_width(char **map)
{
	int		i;
	int		width;
	char	**splits;

	i = 0;
	splits = ft_split(map[0], ' ');
	if (!splits)
		return (0);
	width = fdf_map_get_height(splits);
	ft_split_destroy(splits);
	while (map[i])
	{
		splits = ft_split(map[i], ' ');
		if (!splits)
			return (0);
		if (fdf_map_get_height(splits) != width)
			return (ft_split_destroy(splits), 0);
		ft_split_destroy(splits);
		i++;
	}
	return (width);
}

static int	fdf_fill_map(t_map *map, char **datas)
{
	int		i;
	int		j;
	char	**line;

	i = 0;
	while (i < map->height)
	{
		map->data[i] = ft_calloc(sizeof(t_point), map->width);
		if (!map->data[i])
			return (0);
		j = 0;
		line = ft_split(datas[i], ' ');
		if (!line)
			return (0);
		while (j < map->width)
		{
			map->data[i][j].x = i;
			map->data[i][j].y = j;
			map->data[i][j].z = ft_atoi(line[j]);
			j++;
		}
		ft_split_destroy(line);
		i++;
	}
	return (1);
}

t_map	*fdf_get_map(char *input_path)
{
	t_map	*map;
	char	**lines;
	char	*file;

	file = fdf_get_file(input_path);
	if (!file)
		return (NULL);
	lines = ft_split(file, '\n');
	free(file);
	map = malloc(sizeof(t_map));
	map->height = fdf_map_get_height(lines);
	map->width = fdf_map_get_width(lines);
	if (!map->width)
		return (ft_split_destroy(lines), free(map),
			ft_printf("Error : Incorrect map format.\n"), NULL);
	map->data = ft_calloc(sizeof(int *), map->height);
	fdf_fill_map(map, lines);
	return (map);
}
