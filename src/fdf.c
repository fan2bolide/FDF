/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:09:20 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/11 09:33:02 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void put_point_on_window(void *mlx, void *win, int x, int y, t_map *map, int height)
{
	x = (x * 100) / map->width;
	x = (x * 400) / 100;
	y = (y * 100) / map->height;
	y = (y * 400) / 100;
	for	(int i = 0; i < x + 3 ; i++)
		for (int j = 0; j < y + 3 ; j++)
			mlx_pixel_put(mlx, win, x + i - (5 * height), y + j - (5 * height), 0x000000);
	ft_printf("pixel put on %d:%d\n", x - (5 * height), y - (5 * height));
}

void sighandle(int sig)
{
	(void)sig;
	ft_printf("received signal\n");
}

int	frame_rendering(void *st)
{
	ft_printf("salut\n");
	pause();
	mlx_destroy_window(((t_st *)st)->mlx, ((t_st *)st)->win);
	ft_printf("Finished execution, exiting program.\n");
	exit(0);
}

#include <signal.h>
int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	*map;
	int i;
	int j;

	signal(SIGINT, sighandle);
	if (argc != 2)
		return (write(1, "Error : one argument needed : exiting program\n", 46), 1);
	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 400, 400);
	win = mlx_new_window(mlx, 400, 400, "c moi wesh");
	for	(int x = 0; x < 400 ; x++)
		for (int y = 0; y<400 ; y++)
			mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
	map = fdf_get_map(argv[1]);
	if (!map)
		return (1);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->data[i][j])
				put_point_on_window(mlx, win, j, i, map, map->data[i][j]);
			j++;
		}
		i++;
	}
	free(map);
	t_st	*st;
	st = malloc(sizeof (t_st));
	st->mlx = mlx;
	st->win = win;
	mlx_loop_hook(mlx, frame_rendering, st);
	mlx_loop(mlx);
	return (0);
}
