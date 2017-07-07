/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/07 10:30:54 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

int	verif_row(char *map_content, t_infos *infos)
{
	int	nb;
	int	x;
	int	y;

	nb = ft_atoi(map_content);
	/* PARALELLE Transforms/
	x = infos->current_pixel->x; //+ cste * infos->current_pixel->z;
	y = infos->current_pixel->y; // + (cste / 2) * infos->current_pixel->z;*/

	/* ISOMETRIC Transforms */
	x = infos->current_pixel->x - infos->current_pixel->y;
	y = (infos->current_pixel->x + infos->current_pixel->y) / 2;
	x = x + infos->current_pixel->z / 2 + 142;
	y = y - infos->current_pixel-> z / 2 + 70;
	if (nb == 0)
		infos->current_pixel->color = mlx_get_color_value(infos->mlx, 0x00FFFFFF);
	else
		infos->current_pixel->color = mlx_get_color_value(infos->mlx, 0x00FF0000 / abs (infos->current_pixel->z));
	infos->img_data[y * infos->size_line + x * ((infos->bpp) / 8)] =  infos->current_pixel->color;
	//TO DO: Afficher et relier les points selon l'altitude
	//lier(infos);
	return (VERIF_OK);
}

int	draw(t_infos *infos)
{
	char	**map_content;
	char	**cursor;
	char	*line;
	int		x;
	int		y;
	int		count;
//	int		i;

	y = 0;
	line = NULL;
	printf("\n Begin DRAWING IMAGE IM MERORY.. ");
	infos->map->coordinates = (t_pixel **)malloc(sizeof(t_pixel *));
	infos->map->nb_pixels = 0;
	while (get_next_line(infos->current_fd, &line)) //lecture de la map/
	{
		/* Parvenir a stocker l'ensemble des points dans un tableau de pixels*/
		x = 0;
		count = 0;
		map_content = (ft_strsplit(line, SEPARATING_STRING));
		cursor = map_content;
		while (*cursor++)
			count++;
		printf("\nNB A MALLOC ===> %d", count);
		infos->map->coordinates[y] = (t_pixel *)malloc(sizeof(t_pixel) * count);
		while (*map_content)
		{
			infos->current_pixel->x = x;
			infos->current_pixel->y = y;
			infos->current_pixel->z = ft_atoi(*map_content);
		/*	if (x != 0)
			{
				// Assigner le pixel du haut

			}
			if (y != 0)
			{
				//assigner le pixel de gauche
			}*/
			(infos->map->coordinates)[y][x] = *infos->current_pixel;
			if (x != 0) // Il y a un pixel a gauche
				(infos->map->coordinates)[y][x].left = &(infos->map->coordinates)[y][x - 1];
			if (y != 0) // Il y a un pixel au dessus
				(infos->map->coordinates)[y][x].up = &(infos->map->coordinates)[y - 1][x];
			//printf("\nPixel(%d, %d) = %d", infos->map->coordinates[y][x].x, infos->map->coordinates[y][x].y, infos->map->coordinates[y][x].z);
			verif_row(*map_content, infos);
			map_content++;
			infos->map->nb_pixels++;
			x++;
		}
		y++;
	}
	/*	i = 0;
		printf("\n NOMBRE DE PIXELS ==> %d", infos->map->nb_pixels);
		while (i < infos->map->nb_pixels)
		{
			printf("\n\tPIXELS %d => (%d, %d)", i, (infos->map->coordinates[i]->x), (infos->map->coordinates[i]->y));
			i++;
		}*/
	mlx_put_image_to_window(infos->mlx,infos->win, infos->ptr_img, 0, 0);
	return (1);
}

int	key_hook(int keycode, t_infos *infos)
{
	switch (keycode)
	{
		case 123: /* LEFT*/
			mlx_string_put(infos->mlx, infos->win, 0, infos->key_pressed += 21, 0x00FFFF00, "Key Pressed: <");
			printf("\nLEFT Key pressed");

			break;
		case 124: /* RIGHT */
			mlx_string_put(infos->mlx, infos->win, 0, infos->key_pressed += 21, 0x00FFFF00, "Key Pressed: >");
			printf("\n RIGHT Key pressed");
			break;
		case 126: /* UP */
			mlx_string_put(infos->mlx, infos->win, 0, infos->key_pressed += 21, 0x00FFFF00, "Key Pressed: ^");
			printf("\nUP Key pressed");
			break;
		case 125: /* DOWN */
			mlx_string_put(infos->mlx, infos->win, 0, infos->key_pressed += 21, 0x00FFFF00, "Key Pressed: v");
			printf("\n DOWN Key pressed");
			break;
		case 53: /* ECHAP */
			printf("\n*** END OF FDF ***");
			mlx_destroy_image(infos->mlx, infos->ptr_img);
			exit (0);
		default:
			mlx_string_put(infos->mlx, infos->win, 0, infos->key_pressed += 21, 0x00FFFF00, "ANY key Pressed");
			printf("\n Key pressed in window %p: %d", (infos->win), keycode);
	}
	return (keycode);
}

int	expose_hook(t_infos *infos)
{
	infos->key_pressed = 0;
	draw(infos);
//	mlx_put_image_to_window(infos->mlx,infos->win, infos->ptr_img, 0, 0);
	return (0);
}

int	check_map(t_infos *infos)
{
	/* MLX Setup */
	write(1, "\n BEGIN Setup\n", 14);
	infos->mlx = mlx_init(infos);
	if (!infos->mlx)
	{
		printf("\nErreur création connexion");
		return (-8);
	}
	infos->win = mlx_new_window(infos->mlx, WIDTH, HEIGHT, "FDF 42");
	printf("\nMLX --> %p", infos->mlx);
	printf("\nWIN --> %p", infos->win);
	infos->ptr_img = mlx_new_image(infos->mlx, WIDTH, HEIGHT);
	infos->img_data = (int *)mlx_get_data_addr(infos->ptr_img, &(infos->bpp), &(infos->size_line), &(infos->endian));
	printf("\nSETup OK!\n");
	printf("\n\tBits par pixel ==> %d\n", infos->bpp);
	printf("\n\tSize line ==> %d", infos->size_line);
//	draw(infos);
	/*KEY_LOOP*/
	mlx_key_hook(infos->win, key_hook, infos);
	mlx_expose_hook(infos->win, expose_hook, infos);
	mlx_loop(infos->mlx);
	return (MAP_OK);
}

int main(int ac, char **av)
{
	t_params	*params;

	params = (t_params*)malloc(sizeof(t_params));
	params->infos = (t_infos *)malloc(sizeof(t_infos));
	if (!(params && params->infos))
		return (-1);
	if (ac == 2)
	{
		int	fd = open(av[1], O_RDONLY);

		if (fd < 0)
			return (OPEN_FILE_ERROR);
		params->infos->current_fd = fd;
		params->infos->bpp = 0;
		params->infos->size_line = 0;
		params->infos->endian = 0;
		params->infos->current_pixel = (t_pixel *)malloc(sizeof(t_pixel));
		params->infos->map = (t_map *)malloc(sizeof(t_map));
		if (!(params->infos->current_pixel))
			return(ERROR_PIXEL_PTR);
		printf("\nOUverture du fichier ==> %d", fd);
		printf("\nTest: FT_ATOI(8,0xFFFFFF) ==> %d", ft_atoi("8,0xFFFFFF"));
		printf("\nTest: FT_ATOI(F) ==> %d", ft_atoi("F"));
		printf("\nTest: FT_ATOI(0xFFFFFF) ==> %d", ft_atoi("0xFFFFFF"));
		printf("\nTest 2: 0xFFFFFF) ==> %d", 0xFFFFFF);
		check_map(params->infos);
		printf("\n%s ===> OK", av[1]);
		return (0);
	}
	free(params->infos->current_pixel);
	return (-1);
}
