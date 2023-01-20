/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 06:15:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/20 05:28:18 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# ifndef ESC_KEY
#  define ESC_KEY 53
# endif

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
	int		x;
	int		y;
	int		z;
}			t_point;

typedef struct s_map
{
	t_point	**data;
	int		width;
	int		height;
}			t_map;

typedef struct s_fdf
{
	void	*win;
	void	*mlx;
	t_point	win_size;
	t_data	img;
}			t_fdf;

void		fdf_mlx_config(t_fdf *fdf);
void		fdf_image_handling(t_fdf *fdf, t_map *map);
void		fdf_pixel_put(t_data *data, int x, int y, int color);
t_map		*fdf_get_map(char *input_path);
int			fdf_map_get_highest(t_map *map);
int			fdf_map_get_lowest(t_map *map);
void		fdf_map_destroy(t_map *map);
void		fdf_draw_lines(t_fdf *fdf, t_map *map);
void		fdf_map_get_isometrical(t_map *map, t_fdf *fdf);
void		fdf_center_in_frame(t_map *map, t_fdf *fdf);
t_list		*fdf_list_from_file(char *input_path);
void		fdf_tab_destroy(t_point **tab, int height);
size_t		count_strs(const char *s, char c);

# endif
