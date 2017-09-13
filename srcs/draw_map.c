/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 05:55:10 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/13 23:05:17 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

void	horizontal_draw(t_infos *infos, int *line, int *column)
{
	int	i;
	int	j;

	i = *line;
	j = *column;
	infos->current_color = abs(infos->map->coordinates[i][j].z \
			+ infos->map->coordinates[i][j + 1].z);
	draw_line(infos, &(infos->map->coordinates[i][j]), \
			&(infos->map->coordinates[i][j + 1]));
	*column = j + 1;
}

void	vertical_draw(t_infos *infos, int *line, int *column)
{
	int	i;
	int	j;

	i = *line;
	j = *column;
	infos->current_color = abs(infos->map->coordinates[i][j].z \
			+ infos->map->coordinates[i + 1][j].z);
	draw_line(infos, &(infos->map->coordinates[i][j]),\
			&(infos->map->coordinates[i + 1][j]));
	*line = i + 1;
}

void	load_pixel(t_infos *infos)
{
	int	i;
	int	j;

	i = 0;
	while (i < infos->map->nb_lines)
	{
		j = 0;
		while (j < infos->map->nb_columns - 1)
			horizontal_draw(infos, &i, &j);
		i++;
	}
	j = 0;
	while (j < infos->map->nb_columns)
	{
		i = 0;
		while (i < infos->map->nb_lines - 1)
			vertical_draw(infos, &i, &j);
		j++;
	}
}
