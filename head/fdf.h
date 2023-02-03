/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 06:15:40 by bajeanno          #+#    #+#             */
/*   Updated: 2023/01/25 01:28:59 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <math.h>
# define ESC_KEY 53
# define MINUS_KEY 6
# define PLUS_KEY 7
# define UP_KEY 126
# define DOWN_KEY 125
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define DEFAULT_WIN_SIZE 1080
# define ALLOC_ERR "Error: allocation error occured, aborting\n"
# define WRONG_MAP "Error: wrong map format, aborting\n"
# define USAGE "Error: fdf usage: ./fdf <map_path> [-s <win_size>]\n"
# define NO_FILE "Error: "
# define EMPTY_FILE "Error: empty file\n"

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
	float		x;
	float		y;
	float		z;
}			t_point;

typedef struct s_map
{
	t_point	**data;
	int		width;
	int		height;
	float	zoom_scale;
	float	height_scale;
}			t_map;

typedef struct s_fdf
{
	void	*win;
	void	*mlx;
	t_point	win_size;
	t_point	shift;
	t_data	img;
	t_map	*map;
}			t_fdf;

void		fdf_mlx_config(t_fdf *fdf);
void		fdf_image_handling(t_fdf *fdf);
void		fdf_pixel_put(t_data *data, int x, int y, int color);
t_map		*fdf_get_map(char *input_path);
int			fdf_map_get_highest(t_map *map);
int			fdf_map_get_lowest(t_map *map);
void		fdf_map_destroy(t_map *map);
void		fdf_draw_lines(t_fdf *fdf, int color);
void		fdf_map_get_isometrical(t_fdf *fdf);
void		fdf_center_in_frame(t_fdf *fdf);
t_list		*fdf_list_from_file(char *input_path);
void		fdf_tab_destroy(t_point **tab, int height);
size_t		count_strs(const char *s, char c);
int			fdf_update_frame(t_fdf *fdf);

#endif
