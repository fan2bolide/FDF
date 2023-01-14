/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/14 17:10:26 by bajeanno         ###   ########lyon.fr   */
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

void	point_get_iso_coords(t_point *point, int mult, t_map *map)
{
	int	x;
	int	y;

	(void)map;
	x = ((*point).x) * mult;
	y = ((*point).y) * mult;
	(*point).x = (x - y) * cos(3 * M_PI_4);
	(*point).y = ((x + y) * sin(3 * M_PI_4) * sqrt(0.66)) - (*point).z;
}

void	fdf_put_line(t_fdf *fdf, t_point a, t_point b)
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
	int i;
	int j;

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

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	t_map	*map;
	int i;
	int j;
	int mult;

	if (argc != 2)
		return (write(1, "Error : one argument needed : exiting program\n", 46), 1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->mlx = mlx_init();
	fdf->data.img = mlx_new_image(fdf->mlx, 800, 800);
	fdf->win_size.x = 1920;
	fdf->win_size.y = 1080;
	fdf->win = mlx_new_window(fdf->mlx, fdf->win_size.x, fdf->win_size.y, "c moi wesh");
	map = fdf_get_map(argv[1]);
	if (!map)
		return (1);
	mult = (ft_min(fdf->win_size.y, fdf->win_size.x) / ft_max(map->width, map->height)) * 0.9;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			point_get_iso_coords(map->data[i] + j++, mult, map);
		}
		i++;
	}
	ft_printf("%d\n", mult / ft_max(map->height, map->width));
	t_point shift;
	shift.x = fdf->win_size.x / 2 - map->data[map->height / 2][map->width / 2].x;
	shift.y = fdf->win_size.y / 2 - map->data[map->height / 2][map->width / 2].y - ((mult / ft_max(map->height, map->width)) * map->data[map->height / 2][map->width / 2].z);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			map->data[i][j].x += shift.x;
			map->data[i][j].y += shift.y;
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
			mlx_pixel_put(fdf->mlx, fdf->win, map->data[i][j].x, map->data[i][j].y, 0xFFFFFF);
			j++;
		}
		i++;
	}
	fdf_draw_lines(fdf, map);
	ft_printf("finished\n");
	free(map);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
