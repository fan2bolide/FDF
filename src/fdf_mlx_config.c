/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:06:41 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/25 01:47:15 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	fdf_map_destroy(fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
	return (0);
}

void	fdf_update_shift(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_W)
		fdf->shift.y -= 5;
	if (keycode == KEY_A)
		fdf->shift.x -= 5;
	if (keycode == KEY_S)
		fdf->shift.y += 5;
	if (keycode == KEY_D)
		fdf->shift.x += 5;
}

int	fdf_handle_key_press(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		return (close_window(fdf));
	if (keycode == PLUS_KEY)
	{
		fdf->map->zoom_scale *= 1.03;
		fdf->map->height_scale *= 1.03;
	}
	else if (keycode == MINUS_KEY)
	{
		fdf->map->zoom_scale /= 1.03;
		fdf->map->height_scale /= 1.03;
	}
	else if (keycode == UP_KEY)
		fdf->map->height_scale *= 1.03;
	else if (keycode == DOWN_KEY)
		fdf->map->height_scale /= 1.03;
	else if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
		fdf_update_shift(keycode, fdf);
	else
		return (1);
	return (fdf_update_frame(fdf));
}

void	fdf_mlx_config(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, fdf_handle_key_press, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
