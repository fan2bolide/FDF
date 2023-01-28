/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/28 15:20:18 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_init(t_fdf *fdf)
{
	fdf->win_size.y = 1080;
	fdf->win_size.x = fdf->win_size.y * 16 / 9;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_size.x, fdf->win_size.y,
			"FdF");
	if (!fdf->win)
		return (fdf_map_destroy(fdf->map), free(fdf)
			, mlx_destroy_window(fdf->mlx, fdf->win), 1);
	fdf->map->zoom_scale = (ft_min(fdf->win_size.y, fdf->win_size.x)
			/ (fdf_map_get_highest(fdf->map) - fdf_map_get_lowest(fdf->map)));
	fdf->map->height_scale = fdf->map->zoom_scale;
	fdf_map_get_isometrical(fdf);
	fdf->shift.x = 0;
	fdf->shift.y = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (write(1
				, "Error : one argument needed : exiting program\n"
				, 46), 1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->map = fdf_get_map(argv[1]);
	if (!fdf->map)
		return (free(fdf), 1);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (fdf_map_destroy(fdf->map), free(fdf), 1);
	if (fdf_init(fdf))
		return (1);
	fdf_center_in_frame(fdf);
	fdf_image_handling(fdf);
	fdf_mlx_config(fdf);
	return (mlx_loop(fdf->mlx), 0);
}
