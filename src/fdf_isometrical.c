/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:21:17 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/25 00:19:40 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	point_get_iso_coords(t_point *point, float scale, float z_scale)
{
	float	x;
	float	y;

	x = point->x * scale;
	y = point->y * scale;
	point->x = (x - y) * cos(3 * M_PI_4);
	point->y = (((x + y) * sin(3 * M_PI_4)) - (point->z * z_scale)) / 2;
}

void	fdf_map_get_isometrical(t_fdf *fdf)
{
	int		i;
	int		j;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			point_get_iso_coords(fdf->map->data[i] + j, fdf->map->zoom_scale,
				fdf->map->height_scale);
			j++;
		}
		i++;
	}
}
