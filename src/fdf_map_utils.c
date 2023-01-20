/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:15:09 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/18 20:22:45 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_map_get_lowest(t_map *map)
{
	int	min;
	int	i;
	int	j;

	min = map->data[map->height - 1][map->width - 1].y;
	i = map->height - 1;
	while (i >= 0)
	{
		j = map->width - 1;
		while (j >= 0)
		{
			if (map->data[i][j].y < min)
				min = map->data[i][j].y;
			j--;
		}
		i--;
	}
	return (min);
}

int	fdf_map_get_highest(t_map *map)
{
	int	max;
	int	i;
	int	j;

	max = map->data[0][0].y;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->data[i][j].y > max)
				max = map->data[i][j].y;
			j++;
		}
		i++;
	}
	return (max);
}

void	fdf_map_destroy(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
	free(map);
}
