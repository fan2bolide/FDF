/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_center_in_frame.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 14:41:10 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_center_in_frame(t_map *map, t_fdf *fdf)
{
	t_point	shift;
	int		i;
	int		j;

	shift.x = fdf->win_size.x / 2 - map->data[map->height / 2][map->width
		/ 2].x;
	shift.y = fdf->win_size.y / 2 - (fdf_map_get_highest(map)
			+ fdf_map_get_lowest(map)) / 2;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->data[i][j].x += shift.x;
			map->data[i][j].y += shift.y;
			j++;
		}
		i++;
	}
}
