/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_center_in_frame.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:33:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/25 01:29:39 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_center_in_frame(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	offset;

	offset.x = fdf->win_size.x / 2 - fdf->map->data[fdf->map->height
		/ 2][fdf->map->width / 2].x;
	offset.y = fdf->win_size.y / 2 - (fdf_map_get_highest(fdf->map)
			+ fdf_map_get_lowest(fdf->map)) / 2;
	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			fdf->map->data[i][j].x += offset.x + fdf->shift.x;
			fdf->map->data[i][j].y += offset.y + fdf->shift.y;
			j++;
		}
		i++;
	}
}
