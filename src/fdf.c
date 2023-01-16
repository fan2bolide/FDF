/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 16:14:24 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*map;

	if (argc != 2)
		return (write(1,
				"Error : one argument needed : exiting program\n", 46), 1);
	map = fdf_get_map(argv[1]);
	if (!map)
		return (1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (fdf_map_destroy(map), 1);
	fdf->mlx = mlx_init();
	fdf->win_size.y = 1080;
	fdf->win_size.x = fdf->win_size.y * 3 / 2;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_size.x, fdf->win_size.y,
			"FdF");
	fdf_map_get_isometrical(map, fdf);
	fdf_center_in_frame(map, fdf);
	fdf_draw_lines(fdf, map);
	fdf_map_destroy(map);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
