/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 12:12:05 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/07 10:34:39 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"

void	putpixel(t_params *params, int x, int y, int color)
{
	params->infos->img_data[y * params->infos->size_line + x * ((params->infos->bpp) / 8)] =  color; //params->infos->current_pixel->color;
	//mlx_pixel_put(params->mlx, params->win, x, y, color);
}

void	drawpixel_dx(t_params *params, int color)
{
	if (params->dx >= 0)
	{
		params->x = params->x1;
		params->y = params->y1;
		params->xe = params->x2;
	}
	else
	{
		params->x = params->x2;
		params->y = params->y2;
		params->xe = params->x1;
	}
	putpixel(params, params->x, params->y, color);
	while (params->x++ < params->xe)
	{
		if (params->px < 0)
			params->px = params->px + 2 * params->dy1;
		else
		{
			params->y = (((params->dx < 0 && params->dy < 0) || (params->dx > 0\
							&& params->dy > 0)) ? ++params->y : --params->y);
			params->px = params->px + 2 * (params->dy1 - params->dx1);
		}
		putpixel(params, params->x, params->y, color);
	}
}

void	drawpixel_dy(t_params *params, int color)
{
	if (params->dy >= 0)
	{
		params->x = params->x1;
		params->y = params->y1;
		params->ye = params->y2;
	}
	else
	{
		params->x = params->x2;
		params->y = params->y2;
		params->ye = params->y1;
	}
	putpixel(params, params->x, params->y, color);
	while (params->y++ < params->ye)
	{
		if (params->py <= 0)
			params->py = params->py + 2 * params->dx1;
		else
		{
			params->x = (((params->dx < 0 && params->dy < 0) || (params->dx > 0\
							&& params->dy > 0)) ? ++params->x : --params->x);
			params->py = params->py + 2 * (params->dx1 - params->dy1);
		}
		putpixel(params, params->x, params->y, color);
	}
}

void	draw_line(t_params *params, t_pixel *pix1, t_pixel *pix2)
{
	params->x1 = pix1->x;
	params->y1 = pix1->y;
	params->x2 = pix2->x;
	params->y2 = pix2->y;
	params->dx = params->x2 - params->x1;
	params->dy = params->y2 - params->y1;
	params->dx1 = abs(params->dx);
	params->dy1 = abs(params->dy);
	params->px = 2 * params->dy1 - params->dx1;
	params->py = 2 * params->dx1 - params->dy1;
	if (params->dy1 <= params->dx1)
		drawpixel_dx(params, params->current_color);
	else
		drawpixel_dy(params, params->current_color);
}

/*int		main(void)
  {
  int			x;
  int			y;
  t_params	*params;
  t_pixel		*pix1;
  t_pixel		*pix2;

  pix1 = (t_pixel *)malloc(sizeof(t_pixel));
  pix2 = (t_pixel *)malloc(sizeof(t_pixel));
  params = (t_params*)malloc(sizeof(t_params));
  if (!(params && pix1 && pix2))
  exit(-1);
  params->mlx = mlx_init();
  params->win = mlx_new_window(params->mlx, WIDTH, HEIGHT, "Essai segment");
  pix1->x = WIDTH / 2;
  pix1->y = HEIGHT / 2;
  x = 0;
  while (x < WIDTH)
  {
  y = 0;
  while (y < HEIGHT)
  {
  params->current_color = 0x00FFFF00 / (x + 0.5);
  pix2->x = x;
  pix2->y = y;
  draw_line(params, pix1, pix2);
  y += 10;
  }
  x += 10;
  }
  mlx_loop(params->mlx);
  return (0);
  }*/
