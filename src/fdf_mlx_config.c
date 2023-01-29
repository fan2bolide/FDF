/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:06:41 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/29 11:39:09 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	fdf_map_destroy(fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf);
	exit(0);
	return (0);
}

void	fdf_update_shift(int keycode, t_fdf *fdf)
{
	if (keycode == FDF_KEY_W)
		fdf->shift.y -= 5;
	if (keycode == FDF_KEY_A)
		fdf->shift.x -= 5;
	if (keycode == FDF_KEY_S)
		fdf->shift.y += 5;
	if (keycode == FDF_KEY_D)
		fdf->shift.x += 5;
}

int	fdf_handle_key_press(int keycode, t_fdf *fdf)
{
	if (keycode == FDF_ESC_KEY)
		return (close_window(fdf));
	if (keycode == FDF_KEY_X)
	{
		fdf->map->zoom_scale *= 1.03;
		fdf->map->height_scale *= 1.03;
	}
	else if (keycode == FDF_KEY_Z)
	{
		fdf->map->zoom_scale /= 1.03;
		fdf->map->height_scale /= 1.03;
	}
	else if (keycode == FDF_KEY_UP)
		fdf->map->height_scale *= 1.03;
	else if (keycode == FDF_KEY_DOWN)
		fdf->map->height_scale /= 1.03;
	else if (keycode == FDF_KEY_W || keycode == FDF_KEY_A
		|| keycode == FDF_KEY_S || keycode == FDF_KEY_D)
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
