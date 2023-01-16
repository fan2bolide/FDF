/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:21:17 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 16:17:21 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	point_get_iso_coords(t_point *point, int scale)
{
	int	x;
	int	y;

	x = (*point).x * scale * 1.1;
	y = (*point).y * scale;
	(*point).z *= scale;
	(*point).x = (x - y) * cos(3 * M_PI_4);
	(*point).y = (((x + y) * sin(3 * M_PI_4)) - (*point).z) / sqrt(3);
}

void	fdf_map_get_isometrical(t_map *map, t_fdf *fdf)
{
	int	i;
	int	j;
	int	scale;

	scale = (ft_min(fdf->win_size.y, fdf->win_size.x) / ft_max(map->width,
				map->height));
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			point_get_iso_coords(map->data[i] + j, scale);
			j++;
		}
		i++;
	}
}
