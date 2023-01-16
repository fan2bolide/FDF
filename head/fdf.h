/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 06:15:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/16 14:49:39 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int z;
}			t_point;

typedef struct	s_map
{
	t_point **data;
	int	width;
	int	height;
}		t_map;

typedef struct	s_fdf
{
	void	*win;
	void	*mlx;
	t_point	win_size;
	t_data	data;
}			t_fdf;

t_map	*fdf_get_map(char *input_path);
int		fdf_map_get_highest(t_map *map);
int		fdf_map_get_lowest(t_map *map);
void	fdf_draw_lines(t_fdf *fdf, t_map *map);
void	fdf_map_get_isometrical(t_map *map, t_fdf *fdf);
void	fdf_center_in_frame(t_map *map, t_fdf *fdf);

#endif
