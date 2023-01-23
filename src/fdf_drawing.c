/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:13:14 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 20:18:50 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	fdf_put_line(t_fdf *fdf, t_point a, t_point b, int color)
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
		if (round(x) >= 0 && round(x) < fdf->win_size.x && round(y) >= 0
			&& round(y) < fdf->win_size.y)
			fdf_pixel_put(&fdf->img, round(x), round(y), color);
		x += (b.x - a.x) / (float)steps;
		y += (b.y - a.y) / (float)steps;
		i++;
	}
}

void	fdf_draw_lines(t_fdf *fdf, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			if (j < fdf->map->width - 1)
				fdf_put_line(fdf, fdf->map->data[i][j], fdf->map->data[i][j + 1], color);
			if (i < fdf->map->height - 1)
				fdf_put_line(fdf, fdf->map->data[i][j], fdf->map->data[i + 1][j], color);
			j++;
		}
		i++;
	}
}
