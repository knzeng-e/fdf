/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:39:45 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/14 00:19:51 by knzeng-e         ###   ########.fr       */
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
# define ERROR_MALLOC -5
# define ERROR_INIT -6
# define PARSE_ERROR -7
# define SEPARATING_CHAR ' '
# define INVALID_KEY -8
# define WIDTH 1200
# define HEIGHT 900
# define SCALE 6
# define SPEED 6
# define cste 0.5
# define cste2 0.5

# include <libft.h>
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
	int			x_iso;
	int			y_iso;
	int			pixel_color;
};

typedef struct	s_map
{
	t_pixel		**coordinates;
	int			nb_lines;
	int			nb_columns;
}				t_map;

typedef enum	e_view
{
	PARALLEL, ISOMETRIC
}				t_view;

typedef struct	s_infos
{
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
	int			zoom_x;
	int			zoom_y;
	int			has_color;
	int			current_color;
	char		*file;
	void		*mlx;
	void		*win;
	t_pixel		*current_pixel;
	t_map		*map;
	t_view		view;
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
	int			i;
	int			j;
	char		**map_content;
	char		*line;
	t_infos		*infos;
}				t_params;

typedef struct s_function
{
	int			keycode;
	void		(*func)(t_infos *);
}				t_function;

typedef struct	s_key_fonctions
{
	t_function	s_increase_height;
	t_function	s_increase_width;
	t_function	s_decrease_height;
	t_function	s_decrease_width;
	t_function	s_move_left;
	t_function	s_move_right;
	t_function	s_move_up;
	t_function	s_move_down;
	t_function	s_zoom_in;
	t_function	s_zoom_out;
	t_function	s_quit;
	t_function	s_switch_view_isometric;
	t_function	s_switch_view_parallel;
}				t_key_functions;

int		check_map(t_params *params);
int		parse_map(t_params **params);
int		get_map(t_params *params);
int		load_map(t_params *params);
int		expose_hook(t_infos *info);
int		key_hook(int keycode, t_infos *infos);
int		load_map(t_params *params);
void	load_pixel(t_infos *infos);
void	putpixel(t_infos *infos, int x, int y);
void	draw_line(t_infos *infos, t_pixel *pix1, t_pixel *pix2);
void	drawpixel_dx(t_infos *infos);
void	drawpixel_dy(t_infos *infos);
void	draw(t_infos *info);
void	set_values(t_infos *infos, char *d_variable);
void	set_functions(t_function *tab_func);
void	increase_height(t_infos *infos);
void	decrease_height(t_infos *infos);
void	increase_width(t_infos *infos);
void	decrease_width(t_infos *infos);
void	move_left(t_infos *infos);
void	move_right(t_infos *infos);
void	move_up(t_infos *infos);
void	move_down(t_infos *infos);
void	zoom_in(t_infos *infos);
void	zoom_out(t_infos *infos);
void	quit(t_infos *infos);
void	switch_view_isometric(t_infos *infos);
void	switch_view_parallel(t_infos *infos);
#endif
