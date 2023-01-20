/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:31:56 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/20 05:46:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static char	**fdf_get_file(char *input_path)
{
	char	**file;
	t_list	*list;
	t_list	*curr;
	size_t	i;

	list = fdf_list_from_file(input_path);
	file = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!file)
		return (ft_lstclear(&list, free), NULL);
	curr = list;
	i = 0;
	while (curr)
	{
		file[i++] = (char *)curr->content;
		curr = curr->next;
	}
	file[i] = NULL;
	ft_lstclear_mais_pas_trop(&list);
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
	char	*str;

	str = ft_strtrim(map[0], " \n");
	width = (int)count_strs(str, ' ');
	free(str);
	i = 1;
	while (map[i])
	{
		str = ft_strtrim(map[i], " \n");
		if (!str)
			return (0);
		if (width != (int)count_strs(str, ' '))
			return (free(str), 0);
		free(str);
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
			return (fdf_tab_destroy(map->data, map->height), 0);
		j = 0;
		line = ft_split(datas[i], ' ');
		if (!line)
			return (fdf_tab_destroy(map->data, map->height), 0);
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
	char	**file;

	file = fdf_get_file(input_path);
	if (!file)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_split_destroy(file), NULL);
	map->height = fdf_map_get_height(file);
	map->width = fdf_map_get_width(file);
	if (!map->width)
		return (write(2, "Wrong map format, aborting\n", 27), free(map),
			ft_split_destroy(file), NULL);
	map->data = ft_calloc(sizeof(int *), map->height);
	if (!map->data)
		return (ft_split_destroy(file), free(map), NULL);
	fdf_fill_map(map, file);
	ft_split_destroy(file);
	return (map);
}
