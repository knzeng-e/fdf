/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/06/16 18:29:00 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mlx.h>
#include "get_map.h"

int	verif_row(char *map_content, t_infos *infos, int x, int y)
{
	int	nb;

	nb = ft_atoi(map_content);
	/* ISOMETRIC Transforms */
//	x = (x * SCALE) - (y * SCALE);
	//y = ((x * SCALE) + (y * SCALE)) / 2;
	x = x * SCALE + 40;
	y = y * SCALE + 40;
	if (nb == 0)
		infos->img_data[y * WIDTH + x] = 0x00FFFFFF;
	else
		infos->img_data[y * WIDTH + x] = 0x00FF0000;
	//TO DO: Afficher et relier les pointsm selon l'altitude
	return (VERIF_OK);
}

int	draw(t_infos *infos)
{
	char	**map_content;
	char	*line;
	int		x;
	int		y;

	//y = infos->y_orig - 1;
	y = -1;
	line = NULL;
	while (get_next_line(infos->current_fd, &line)) //lecture de la map/
	{
		y++;
		x = -1;
		//x = infos->x_orig - 1;
		map_content = (ft_strsplit(line, SEPARATING_STRING));
		while (*map_content)
		{
			x++;
			infos->current_pixel->x = x;
			infos->current_pixel->y = y;
			infos->current_pixel->z = ft_atoi(*map_content);
			if (verif_row(*map_content, infos, x, y))
			{

			}
			map_content++;
		}
		printf("\n");
	}
	return (0);
}

int	key_hook(int keycode, t_infos *infos)
{
	switch (keycode)
	{
		case 123: /* LEFT*/
			//infos->x_orig -= 1;
			//check_map(infos->current_fd);
			//expose_hook(infos);
			printf("\nLEFT Key pressed");

			break;
		case 124: /* RIGHT */
			//infos->x_orig += 2;
			//draw(infos);
			printf("\n RIGHT Key pressed x ++> %d", infos->x_orig);
			break;
		case 126: /* UP */
			infos->y_orig -= 1;
			//draw(infos);

			printf("\nUP Key pressed");
			break;
		case 125: /* DOWN */
			//infos->y_orig += 1;
			//draw(infos);

			printf("\n DOWN Key pressed");
			break;
		case 53: /* ECHAP */
			printf("\n*** END OF FDF ***");
			exit (0);
		default:
			printf("\n Key pressed in window %p: %d", (infos->win), keycode);
	}
	return (keycode);
}

int	expose_hook(t_infos *infos)
{
	mlx_destroy_image(infos->mlx, infos->ptr_img);
	draw(infos);
	//check_map(infos->current_fd);
	return (0);
}

int	check_map(t_infos *infos)
{
	/* MLX Setup */
	infos->mlx = mlx_init();
	infos->win = mlx_new_window(infos->mlx, WIDTH, HEIGHT, "FDF 42");
	infos->ptr_img = mlx_new_image(infos->mlx, WIDTH, HEIGHT);
	infos->img_data = (int *)mlx_get_data_addr(infos->ptr_img, &(infos->bpp), &(infos->size_line), &(infos->endian));
	infos->x_orig = 0;
	infos->y_orig = 0;
	draw(infos);
	/*KEY_LOOP*/
	mlx_key_hook(infos->win, key_hook, infos);
	mlx_expose_hook(infos->win, expose_hook, infos);
	mlx_put_image_to_window(infos->mlx,infos->win, infos->ptr_img, infos->x_orig, infos->y_orig);
	mlx_loop(infos->mlx);
	//	free(infos);
	return (MAP_OK);
}

int main(int ac, char **av)
{
	t_infos *infos;

	infos = (t_infos *)malloc(sizeof(t_infos));

	if (ac == 2)
	{
		int	fd = open(av[1], O_RDONLY);

		if (!infos || fd < 0)
			return (OPEN_FILE_ERROR);
		infos->current_fd = fd;
		printf("\nOUverture du fichier ==> %d", fd);
		printf("\nTest: FT_ATOI(8,0xFFFFFF) ==> %d", ft_atoi("8,0xFFFFFF"));
		printf("\nTest: FT_ATOI(F) ==> %d", ft_atoi("F"));
		printf("\nTest: FT_ATOI(0xFFFFFF) ==> %d", ft_atoi("0xFFFFFF"));
		printf("\nTest 2: 0xFFFFFF) ==> %d", 0xFFFFFF);
		if (check_map(infos))
		{
			//	printf("\n%s ===> OK", av[1]);
			return (0);
		}
	}
	return (-1);
}
