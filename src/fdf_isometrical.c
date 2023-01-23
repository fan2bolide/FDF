/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_isometrical.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:21:17 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 20:26:40 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	point_get_iso_coords(t_point *point, size_t scale)
{
	int	x;
	int	y;

	x = point->x * scale;
	y = point->y * scale;
	point->x = (x - y) * cos(3 * M_PI_4);
	point->y = (((x + y) * sin(3 * M_PI_4)) - (point->z * scale));
}

void	fdf_map_get_isometrical(t_fdf *fdf)
{
	int		i;
	int		j;
	double	sqrt3;

	sqrt3 = sqrt(3);
	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			point_get_iso_coords(fdf->map->data[i] + j, fdf->map->scale);
			fdf->map->data[i][j++].y /= sqrt3;
		}
		i++;
	}
}
