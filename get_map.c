/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/06/16 16:29:11 by knzeng-e         ###   ########.fr       */
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
	x += 90;
	y += 40;
	infos->ptr_img = mlx_new_image(infos->mlx, WIDTH, HEIGHT);
	infos->img_data = mlx_get_data_addr(infos->ptr_img, &(infos->bpp), &(infos->size_line), &(infos->endian));
	if (nb == 0)
		mlx_pixel_put(infos->mlx, infos->win, (x * SCALE) - (y * SCALE), ((x * SCALE) + (y * SCALE)) / 2, 0x00FFFFFF);
	else
		mlx_pixel_put(infos->mlx, infos->win, (x * SCALE) - (y * SCALE), ((x * SCALE) + (y * SCALE)) / 2, 0x00FF0000);
	//mlx_pixel_put(infos->mlx, infos->win, x * 13, y * 13, 0x00FF0000);
	printf("\n(%d, %d)==> %s", infos->current_pixel->x, infos->current_pixel->y, map_content);
	//TO DO: Afficher et relier les pointsm selon l'altitude
	return (VERIF_OK);
}

int	draw(t_infos *infos)
{
	char	**map_content;
	char	*line;
	int		x;
	int		y;

	y = infos->y_orig - 1;
	line = NULL;
	while (get_next_line(infos->current_fd, &line)) //lecture de la map/
	{
		y++;
		x = infos->x_orig - 1;
		map_content = (ft_strsplit(line, SEPARATING_STRING));
		while (*map_content)
		{
			x++;
			infos->current_pixel->x = x;
			infos->current_pixel->y = y;
			infos->current_pixel->z = ft_atoi(*map_content);
			if (verif_row(*map_content, infos, x, y))
			{
				printf("\n Content => %s == %d", *map_content, ft_str_is_numeric(*map_content));
				//printf("\nInvalid MAP ==> ERROR");
				//return (MAP_ERROR);
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
			infos->x_orig -= 1;
			//check_map(infos->current_fd);
			expose_hook(infos);
			printf("\nLEFT Key pressed");

			break;
		case 124: /* RIGHT */
			infos->x_orig += 42;
			draw(infos);
			printf("\n RIGHT Key pressed");
			break;
		case 126: /* UP */
			infos->y_orig -= 1;
			draw(infos);

			printf("\nUP Key pressed");
			break;
		case 125: /* DOWN */
			infos->y_orig += 1;
			draw(infos);

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
	draw(infos);
	//check_map(infos->current_fd);
	return (0);
}

int	check_map(int fd)
{
	t_infos *infos;

	infos = (t_infos *)malloc(sizeof(t_infos));
	if (!infos || infos->current_fd < 0)
		return (OPEN_FILE_ERROR);
	/* MLX Setup */
	infos->current_fd = fd;
	printf("\nFDF in current fd = %d", infos->current_fd);
	infos->mlx = mlx_init();
	infos->win = mlx_new_window(infos->mlx, WIDTH, HEIGHT, "FDF 42");
	infos->x_orig = 0;
	infos->y_orig = 0;
//	draw(infos);
	/*KEY_LOOP*/
	mlx_key_hook(infos->win, key_hook, infos);
	mlx_expose_hook(infos->win, expose_hook, infos);
	mlx_loop(infos->mlx);
//	free(infos);
	return (MAP_OK);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int	fd = open(av[1], O_RDONLY);

		printf("\nOUverture du fichier ==> %d", fd);
		printf("\nTest: FT_ATOI(8,0xFFFFFF) ==> %d", ft_atoi("8,0xFFFFFF"));
		printf("\nTest: FT_ATOI(F) ==> %d", ft_atoi("F"));
		printf("\nTest: FT_ATOI(0xFFFFFF) ==> %d", ft_atoi("0xFFFFFF"));
		printf("\nTest 2: 0xFFFFFF) ==> %d", 0xFFFFFF);
		if (check_map(fd))
		{
			//	printf("\n%s ===> OK", av[1]);
			return (0);
		}
	}
	return (-1);
}
