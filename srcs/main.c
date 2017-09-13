/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/08/26 19:24:32 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

static void	ft_init_vars(t_params **params, int fd)
{
	(*params)->infos->current_fd = fd;
	(*params)->infos->bpp = 0;
	(*params)->infos->size_line = 0;
	(*params)->infos->endian = 0;
	(*params)->infos->zoom_x = SCALE;
	(*params)->infos->zoom_y = SCALE;
	(*params)->infos->x_orig = 0;
	(*params)->infos->y_orig = 0;
	(*params)->line = NULL;
	(*params)->infos->view = ISOMETRIC;
}

int			ft_init(t_params **params, int fd)
{
	(*params)->infos->mlx = mlx_init();
	(*params)->infos->win = mlx_new_window((*params)->infos->mlx, \
			WIDTH, HEIGHT, "FDF 42");
	ft_init_vars(params, fd);
	(*params)->infos->current_pixel = (t_pixel *)malloc(sizeof(t_pixel));
	if (!((*params)->infos->current_pixel))
		return (ERROR_PIXEL_PTR);
	(*params)->infos->map = (t_map *)malloc(sizeof(t_map));
	if (!((*params)->infos->map))
		return (ERROR_PIXEL_PTR);
	(*params)->infos->map->nb_lines = 0;
	(*params)->infos->ptr_img = mlx_new_image((*params)->infos->mlx, \
			WIDTH, HEIGHT);
	(*params)->infos->img_data = (int *)mlx_get_data_addr((*params)->\
		infos->ptr_img, &((*params)->infos->bpp),\
		&((*params)->infos->size_line)\
		, &((*params)->infos->endian));
	return (1);
}

int			ft_free(t_params **params, int ac)
{
	int	output;

	output = -1;
	if (ac == 2)
	{
		output = 1;
		free((*params)->infos->current_pixel);
		free((*params)->infos->map);
	}
	else
		ft_putstr("Mauvais nombre d'arguments");
	free((*params)->infos);
	free(*params);
	return (output);
}
int			check_errors(t_params *params, int fd)
{
	int	check;

		if (fd < 0)
			check = OPEN_FILE_ERROR;
		else
			if (ft_init(&params, fd) < 0)
				check = ERROR_INIT;
		else
			if (parse_map(&params) < 0 || get_map(params) < 0)
				check = PARSE_ERROR;
		else
			check = MAP_OK;
		if (check < 0)
			ft_putendl("error: Invalid file");
		return (check);
}

int			main(int ac, char **av)
{
	t_params	*params;
	int			fd;

	params = (t_params*)malloc(sizeof(t_params));
	params->infos = (t_infos *)malloc(sizeof(t_infos));
	if (!(params && params->infos))
	{
		if (params)
			free(params);
		return (-1);
	}
	if (ac == 2)
	{
		params->infos->file = av[1];
		fd = open(params->infos->file, O_RDONLY);
		if (check_errors(params, fd) < 0)
		{
			ft_free(&params, ac);
			return (MAP_ERROR);
		}
		draw(params->infos);
	}
	return (ft_free(&params, ac));
}
