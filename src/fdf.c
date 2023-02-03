/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/26 01:46:40 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_check_args(int argc, char **argv, t_fdf *fdf)
{
	if (argc == 4)
		if (ft_strequ(argv[2], "-s"))
			return (fdf->win_size.y = (float)ft_atoi(argv[3]), 0);
	if (argc != 2)
		return (write(2, USAGE, ft_strlen(USAGE)), 1);
	return (0);
}

static int	fdf_init(t_fdf *fdf)
{
	fdf->win_size.x = fdf->win_size.y * 16 / 9;
	fdf->win = mlx_new_window(fdf->mlx, (int)fdf->win_size.x,
			(int)fdf->win_size.y, "FdF");
	if (!fdf->win)
		return (fdf_map_destroy(fdf->map),
			mlx_destroy_window(fdf->mlx, fdf->win), 1);
	fdf->map->zoom_scale = (float)(ft_min((int)fdf->win_size.y,
				(int)fdf->win_size.x)
			/ (fdf_map_get_highest(fdf->map)
				- fdf_map_get_lowest(fdf->map)));
	fdf->map->height_scale = fdf->map->zoom_scale;
	fdf_map_get_isometrical(fdf);
	fdf->shift.x = 0;
	fdf->shift.y = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	fdf.win_size.y = DEFAULT_WIN_SIZE;
	if (fdf_check_args(argc, argv, &fdf))
		return (1);
	fdf.map = fdf_get_map(argv[1]);
	if (!fdf.map)
		return (1);
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (fdf_map_destroy(fdf.map), 1);
	if (fdf_init(&fdf))
		return (1);
	fdf_center_in_frame(&fdf);
	fdf_image_handling(&fdf);
	fdf_mlx_config(&fdf);
	return (mlx_loop(fdf.mlx), 0);
}
