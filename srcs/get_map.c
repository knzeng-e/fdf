/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 23:38:48 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/08/26 19:21:52 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

int	expose_hook(t_infos *infos)
{
	infos->key_pressed = 0;
	ft_bzero(infos->img_data, HEIGHT * infos->size_line);
	load_pixel(infos);
	mlx_clear_window(infos->mlx, infos->win);
	mlx_put_image_to_window(infos->mlx, infos->win, infos->ptr_img, 0, 0);
	mlx_string_put(infos->mlx, infos->win, WIDTH / 2, 0, 0x00FFFF00,\
			infos->file);
	return (0);
}

int	key_hook(int keycode, t_infos *infos)
{
	t_function tab_functions[13];
	int			index;

	index = 0;
	set_functions(tab_functions);
	while (tab_functions[index].keycode != keycode)
	{
		if (index == 13)
			return (INVALID_KEY);
		index++;
	}
	tab_functions[index].func(infos);
	return (keycode);
}

int	mouse_hook(int button, int x, int y, t_infos *infos)
{
	ft_putstr("\nClick button ");
	ft_putnbr(button);
	ft_putstr(" en ( ");
	ft_putnbr(x);
	ft_putstr(", ");
	ft_putnbr(y);
	ft_putendl(")");
	if (button == 1)
	{
		infos->x_orig = x - (WIDTH / 4);
		infos->y_orig = y - (HEIGHT / 3);
	}
	if (button == 4)
		infos->y_orig += SPEED;
	if (button == 6)
		infos->x_orig += SPEED;
	if (button ==  7)
		infos->x_orig -= SPEED;
	if (button == 5)
		infos->y_orig -= SPEED;
	expose_hook(infos);
	return (x + y);
}

void	draw(t_infos *infos)
{
	mlx_put_image_to_window(infos->mlx, infos->win, infos->ptr_img, 0, 0);
	mlx_key_hook(infos->win, key_hook, infos);
	mlx_mouse_hook(infos->win, mouse_hook, infos);
	mlx_expose_hook(infos->win, expose_hook, infos);
	mlx_loop(infos->mlx);
}
