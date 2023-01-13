/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/12 20:39:18 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->data.img);
	free(fdf);
	exit(0);
	return(0);
}

t_point	get_point(int x, int y, int z)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

void	point_get_iso_coords(t_point *point, t_map *map)
{
	t_point point2;

	point2.x = ((((*point).x * 100) / map->width) * 400 / 100);
	point2.y = ((((*point).y * 100) / map->height) * 400 / 100);
	point2.z = (*point).z;
	(*point).x = -(point2.x - point2.y) * cos(M_PI_4);
	(*point).y = (point2.x + point2.y) * sin(M_PI_4) - (5 * point2.z);
}

void	fdf_put_line(t_fdf *fdf, t_point a, t_point b)
{
	int i;
	int j;
	int coeff_dir;

	coeff_dir = (b.y - a.y) / (b.x - a.x);
	i = a.y;
	while (i < b.y)
	{
		j = 0;
		if (coeff_dir < 0)
			while (j++ < coeff_dir)
				mlx_pixel_put(fdf->mlx, fdf->win, i, j + a.x, 0xFFFFFF);
		else
			while (j-- > coeff_dir)
				mlx_pixel_put(fdf->mlx, fdf->win, i, j + a.x, 0xFFFFFF);
		i++;
	}
}

void	fdf_draw_lines(t_fdf *fdf, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width - 1)
		{
			fdf_put_line(fdf, map->data[i][j], map->data[i][j + 1]);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*map;
	int i;
	int j;

	if (argc != 2)
		return (write(1, "Error : one argument needed : exiting program\n", 46), 1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->mlx = mlx_init();
	fdf->data.img = mlx_new_image(fdf->mlx, 800, 800);
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "c moi wesh");
	map = fdf_get_map(argv[1]);
	if (!map)
		return (1);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			point_get_iso_coords(map->data[i] + j, map);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			mlx_pixel_put(fdf->mlx, fdf->win, map->data[i][j].x + 500, map->data[i][j].y, 0xFFFFFF);
			j++;
		}
		i++;
	}
	fdf_draw_lines(fdf, map);
	//put_point_on_image(fdf, map->data[i][j], map);
	ft_printf("finished\n");
	free(map);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
