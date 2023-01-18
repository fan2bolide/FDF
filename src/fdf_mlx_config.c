/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 19:06:41 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/18 19:18:42 by bajeanno         ###   ########lyon.fr   */
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

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_KEY)
		return (close_window(fdf));
	return (0);
}

void	fdf_mlx_config(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
