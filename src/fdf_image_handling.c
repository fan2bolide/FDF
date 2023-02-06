/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:03:26 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 20:27:34 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_image_handling(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->win_size.x, fdf->win_size.y);
	if (!fdf->img.img)
		return (mlx_destroy_window(fdf->mlx, fdf->win), \
		mlx_destroy_display(fdf->mlx), free(fdf->mlx), \
		fdf_map_destroy(fdf->map), exit(1), (void)0);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, \
	&fdf->img.line_length, &fdf->img.endian);
	fdf_draw_lines(fdf, 0xFFFFFF);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
