/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:21:17 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 03:38:05 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	point_get_iso_coords(t_point *point, int scale)
{
	int	x;
	int	y;

	x = point->x * scale;
	y = point->y * scale;
	point->x = (x - y) * cos(3 * M_PI_4);
	point->y = (((x + y) * sin(3 * M_PI_4)) - (point->z * scale));
}

void	fdf_map_get_isometrical(t_map *map, t_fdf *fdf)
{
	int		i;
	int		j;
	int		scale;
	double	sqrt3;

	sqrt3 = sqrt(3);
	scale = (ft_min(fdf->win_size.y, fdf->win_size.x)
			/ (fdf_map_get_highest(map) - fdf_map_get_lowest(map)));
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			point_get_iso_coords(map->data[i] + j, scale);
			map->data[i][j++].y /= sqrt3;
		}
		i++;
	}
}
