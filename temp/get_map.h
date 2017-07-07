/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:39:45 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/07 10:22:14 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_MAP_H
# define GET_MAP_H
# define VERIF_OK 2
# define MAP_OK 1
# define MAP_ERROR -2
# define OPEN_FILE_ERROR -1
# define ERROR_PIXEL_PTR -3
# define ERROR_DATA -4
# define SEPARATING_STRING ' '
# define WIDTH 1000
# define HEIGHT 600
# define SCALE 2
# define cste 0.5
# define cste2 0.5

# include <libft.h>
# include <stdio.h>
# include <math.h>
# include <sys/stat.h>
#include <fcntl.h>
# include "mlx.h"

typedef struct	s_pixel t_pixel;
struct	s_pixel
{
	int			x;
	int			y;
	int			z;
	int			color;
	t_pixel		*left;
	t_pixel		*right;
	t_pixel		*up;
	t_pixel		*down;
};

typedef struct	s_map
{
	t_pixel		**coordinates;
	int			nb_pixels;
}				t_map;

typedef struct	s_infos
{
	int			*win;
	int			*mlx;
	int			x_orig;
	int			y_orig;
	int			current_fd;
	int			fst_line_size;
	int			size_line;
	int			endian;
	int			bpp;
	int			*ptr_img;
	int			*img_data;
	int			key_pressed;
	t_pixel		*current_pixel;
	t_map		*map;
}				t_infos;

typedef struct	s_params
{
	int			x;
	int			y;
	int			ye;
	int			xe;
	int			dx;
	int			dy;
	int			dx1;
	int			dy1;
	int			px;
	int			py;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			current_color;
	void		*mlx;
	void		*win;
	t_infos		*infos;
}				t_params;

int		check_map(t_infos *infos);
int		expose_hook(t_infos *infos);
void	drawpixel_dx(t_params *params, int color);
void	drawpixel_dy(t_params *params, int color);
void	draw_line(t_params *params, t_pixel *pix1, t_pixel *pix2);
#endif
