/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/12 21:49:22 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

int		check_map(t_params *params)
{
	char    **map_content;
	char    *line;
	int      count;

	line = NULL;
	while (get_next_line(params->infos->current_fd, &line))
	{
		count = 0;
		map_content = (ft_strsplit(line, SEPARATING_CHAR));
		if (!(map_content))
			return (-10);
		while (map_content[count])
			count++;
		if (params->infos->map->nb_lines == 0)
			params->infos->map->nb_columns = count;
		else
			if (count != params->infos->map->nb_columns)
				return (MAP_ERROR);
		params->infos->map->nb_lines++;
	}
	close(params->infos->current_fd);
	return (MAP_OK);
}

void	set_coordinates(t_params *params, int i, int j)
{
	int	value;

	value = ft_atoi(*(params->map_content));
	/* definir les coordonnees orthogonales */
	params->infos->map->coordinates[i][j].y = i / cste;
	params->infos->map->coordinates[i][j].x = j / cste;
	params->infos->map->coordinates[i][j].z = value;
	params->infos->map->coordinates[i][j].x -= value;
	params->infos->map->coordinates[i][j].y -= value;
	/* definir les coordonnees isometriques */
	params->infos->map->coordinates[i][j].x_iso = (j + i) / cste;
	params->infos->map->coordinates[i][j].y_iso = (i - j);
	params->infos->map->coordinates[i][j].x_iso -= value;
	params->infos->map->coordinates[i][j].y_iso -= value / cste;
}

int		load_map(t_params *params)
{
	params->infos->current_fd = open(params->infos->file, O_RDONLY);
	if (params->infos->current_fd < 0)
		return (OPEN_FILE_ERROR);
	params->i = -1;
	while(get_next_line(params->infos->current_fd, &(params->line)))
	{
		params->i++;
		params->map_content = ft_strsplit(params->line, SEPARATING_CHAR);
		if (!params->map_content)
			return (-6);
		params->infos->map->coordinates[params->i] = \
		(t_pixel *)malloc(sizeof(t_pixel) * params->infos->map->nb_columns);
		if (params->infos->map->coordinates[params->i] == NULL)
			return (ERROR_MALLOC);
		params->j = 0;
		while (*(params->map_content))
		{
			set_coordinates(params, params->i, params->j);
			params->j++;
			params->map_content++;
		}
	}
	return (MAP_OK);
}

int		get_map(t_params *params)
{
	int	i;
	int	j;

	i = params->infos->map->nb_lines;
	j  = params->infos->map->nb_columns;
	params->infos->map->coordinates =\
							(t_pixel **)malloc(sizeof(t_pixel *) * i * j);
	if (!(params->infos->map->coordinates))
		return (ERROR_MALLOC);
	if (load_map(params) < 0)
		return (MAP_ERROR);
	return (MAP_OK);
}

int		parse_map(t_params **params)
{
	if (check_map(*params) == MAP_ERROR)
		return (MAP_ERROR);
	return (MAP_OK);
}
