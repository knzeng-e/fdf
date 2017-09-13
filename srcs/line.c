/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 12:12:05 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/08/26 14:40:41 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

void	putpixel(t_infos *infos, int x, int y)
{
	int	final_color;
	int	basic_color;

	if (infos->current_color)
	{
		basic_color = 0x00FF0000 / infos->current_color;
		final_color = mlx_get_color_value(infos->mlx, basic_color);
	}
	else
		final_color = mlx_get_color_value(infos->mlx, 0x00FFFFFF);
	x += WIDTH / 4 + infos->x_orig;
	y += HEIGHT / 3 + infos->y_orig;
	if ((y >= 0 && y <= HEIGHT) && (x  >= 0 && x <= WIDTH))
		if ((y * WIDTH + x) <= (WIDTH * HEIGHT))
			infos->img_data[y * WIDTH + x] =  final_color;
}

void	drawpixel_dx(t_infos *infos)
{
	set_values(infos, "dx");
	putpixel(infos, infos->x, infos->y);
	while (infos->x++ < infos->xe)
	{
		if (infos->px < 0)
			infos->px = infos->px + 2 * infos->dy1;
		else
		{
			infos->y = (((infos->dx < 0 && infos->dy < 0) || (infos->dx > 0\
							&& infos->dy > 0)) ? ++infos->y : --infos->y);
			infos->px = infos->px + 2 * (infos->dy1 - infos->dx1);
		}
		putpixel(infos, infos->x, infos->y);
	}
}

void	drawpixel_dy(t_infos *infos)
{
	set_values(infos, "dy");
	putpixel(infos, infos->x, infos->y);
	while (infos->y++ < infos->ye)
	{
		if (infos->py <= 0)
			infos->py = infos->py + 2 * infos->dx1;
		else
		{
			infos->x = (((infos->dx < 0 && infos->dy < 0) || (infos->dx > 0\
							&& infos->dy > 0)) ? ++infos->x : --infos->x);
			infos->py = infos->py + 2 * (infos->dx1 - infos->dy1);
		}
		putpixel(infos, infos->x, infos->y);
	}
}

void	draw_line(t_infos *infos, t_pixel *pix1, t_pixel *pix2)
{
	infos->x1 = (infos->view == PARALLEL ? pix1->x : pix1->x_iso);
	infos->y1 = (infos->view == PARALLEL ? pix1->y : pix1->y_iso);
	infos->x2 = (infos->view == PARALLEL ? pix2->x : pix2->x_iso);
	infos->y2 = (infos->view == PARALLEL ? pix2->y : pix2->y_iso);
	infos->x1 *= infos->zoom_x;
	infos->y1 *= infos->zoom_y;
	infos->x2 *= infos->zoom_x;
	infos->y2 *= infos->zoom_y;
	infos->dx = infos->x2 - infos->x1;
	infos->dy = infos->y2 - infos->y1;
	infos->dx1 = abs(infos->dx);
	infos->dy1 = abs(infos->dy);
	infos->px = 2 * infos->dy1 - infos->dx1;
	infos->py = 2 * infos->dx1 - infos->dy1;
	if (infos->dy1 <= infos->dx1)
		drawpixel_dx(infos);
	else
		drawpixel_dy(infos);
}
