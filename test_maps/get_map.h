/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:39:45 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/06/16 18:23:51 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_MAP_H
# define GET_MAP_H
# define VERIF_OK 2
# define MAP_OK 1
# define MAP_ERROR -2
# define OPEN_FILE_ERROR -1
# define ERROR_LINE_SIZE -3
# define ERROR_DATA -4
# define SEPARATING_STRING ' '
# define WIDTH 800
# define HEIGHT 600
# define SCALE 2

# include <libft.h>

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_pixel;

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
	t_pixel		*current_pixel;
}				t_infos;

int	check_map(t_infos *infos);
int	expose_hook(t_infos *infos);
#endif
