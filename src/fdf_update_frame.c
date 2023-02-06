/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_update_frame.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:56:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/25 00:48:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_reset_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		while (j < fdf->map->width)
		{
			fdf->map->data[i][j].x = (float)i;
			fdf->map->data[i][j].y = (float)j;
			j++;
		}
		i++;
	}
}

int	fdf_update_frame(t_fdf *fdf)
{
	ft_bzero(fdf->img.addr, fdf->win_size.x * fdf->win_size.y * 4);
	fdf_reset_map(fdf);
	fdf_map_get_isometrical(fdf);
	fdf_center_in_frame(fdf);
	fdf_draw_lines(fdf, 0xFFFFFF);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
