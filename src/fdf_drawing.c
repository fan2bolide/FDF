/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:13:14 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 14:38:36 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_put_line(t_fdf *fdf, t_point a, t_point b)
{
	int		i;
	int		steps;
	float	x;
	float	y;

	steps = ft_max(abs(b.x - a.x), abs(b.y - a.y));
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, round(x), round(y), 0xFFFFFF);
		x += (b.x - a.x) / (float)steps;
		y += (b.y - a.y) / (float)steps;
		i++;
	}
}

void	fdf_draw_lines(t_fdf *fdf, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (j < map->width - 1)
				fdf_put_line(fdf, map->data[i][j], map->data[i][j + 1]);
			if (i < map->height - 1)
				fdf_put_line(fdf, map->data[i][j], map->data[i + 1][j]);
			j++;
		}
		i++;
	}
}
