/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/23 20:31:33 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		return (write(1,
				"Error : one argument needed : exiting program\n",
				46), 1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->map = fdf_get_map(argv[1]);
	if (!fdf->map)
		return (free(fdf),1);
	fdf->mlx = mlx_init();
	fdf->win_size.y = 1080;
	fdf->win_size.x = fdf->win_size.y * 16 / 9;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_size.x, fdf->win_size.y,
			"FdF");
	fdf->map->scale = (ft_min(fdf->win_size.y, fdf->win_size.x)
			/ (fdf_map_get_highest(fdf->map) - fdf_map_get_lowest(fdf->map)));
	fdf_map_get_isometrical(fdf);
	fdf_center_in_frame(fdf);
	fdf_image_handling(fdf);
	fdf_mlx_config(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
