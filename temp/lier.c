/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lier.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <knzeng-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 18:39:43 by knzeng-e          #+#    #+#             */
/*   Updated: 2017/07/07 11:19:54 by knzeng-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_map.h"


//void	putpixel(int x, int y, t_infos *infos)
void	putpixel(int x, int y, int c)
{
//	infos->img_data[y * infos->size_line + x * ((infos->bpp) / 8)] =  infos->current_pixel->color;
	//mlx_pixel_put(infos->mlx, infos->win, x, y, c);
}

//void	bhm_line(int x1, int y1, int x2, int y2, t_infos *infos)
void	bhm_line(int x1, int y1, int x2, int y2, int c)
{
	int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;

	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		putpixel(x, y, c);
		i = 0;
		while (x < xe)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
		//	delay(0);
			putpixel(x,y, c);
			i++;
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		putpixel(x,y, c);
		i = 0;
		while (y < ye)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			//delay(0);
			putpixel(x,y, c);
			i++;
		}
	}
}



void	lier(t_infos *infos)
{
	//int		dx;
//	int		dy;
//	t_pixel	px;
//	int		py;
	//int		incr_e;
//	int		incr_ne;
//	int		err;
	t_pixel	pix1;
	t_pixel	pix2;

	printf("\nStart drawing lines");
	pix2 = (infos->map->coordinates)[infos->current_pixel->y][infos->current_pixel->x];
/*	if ((pix2.x == 0) && (pix2.y == 0))
	{
		if (pix2.z == 0)
		{
			pix2.color = mlx_get_color_value(infos->mlx, 0x00FFFFFF);
			infos->current_pixel->color = pix2.color;
		}
		else
		{
			pix2.color = mlx_get_color_value(infos->mlx, 0x00FF0000 / abs(pix1.z));
			infos->current_pixel->color = pix2.color;
		}
		infos->img_data[pix2.y * infos->size_line + pix2.x * ((infos->bpp) / 8)] = pix2.color;
	}
	//	if (infos->current_pixel->x != 0)
	if (pix2.x != 0)
	{
		pix1 = (infos->map->coordinates)[infos->current_pixel->y][infos->current_pixel->x - 1];
		printf("\nLiaison (%d, %d) -- (%d, %d)", pix2.x, pix2.y, pix1.x, pix1.y);
	}
	else
	{
		pix1 = (infos->map->coordinates)[infos->current_pixel->y][infos->current_pixel->x];
		printf("\nPIX1 ==> (%d, %d)", pix1.x, pix1.y);
	}
	//lier le pixel precedant (x,y) --> (x - 1, y)*/


		pix1 = (infos->map->coordinates)[infos->current_pixel->y][infos->current_pixel->x - 1];
	//bhm_line(pix1.x, pix1.y, pix2.x, pix2.y, infos);
	bhm_line(pix1.x, pix1.y, pix2.x, pix2.y, 0x00FF0000);
}

/*py = pix2.y;
  dx = pix1.x - pix2.x;
  dy = pix1.y - pix2.y;
  incr_e = 2 * dy;
  incr_ne = 2 * (dy - dx);
  err = 2 * dy - dx;
  px = pix2;
  while (px.x <= pix1.x)
  {
  printf("\nCurrent Pix.x == %d & Pix1.x == %d", px.x, pix1.x);
* Debut Allumage du pixel*
if (px.z == 0)
px.color = mlx_get_color_value(infos->mlx, 0x00FFFFFF);
else
px.color = mlx_get_color_value(infos->mlx, 0x00FF0000 / abs(px.z));
infos->img_data[px.y * infos->size_line + px.x * ((infos->bpp) / 8)] = px.color;
px.x++;
*Fin Allumage du pixel*
if (err >= 0)
{
py += 1;
err += incr_ne;
}
else
{
py += dx/dy;
err += incr_e;
}
}*
if (infos->current_pixel->y != 0)
pix1 = (infos->map->coordinates)[infos->current_pixel->y - 1][infos->current_pixel->x];
else
pix1 = (infos->map->coordinates)[infos->current_pixel->y][infos->current_pixel->x];
//lier le pixel precedant (x,y) --> (x, y - 1)
//ATTENTION A L'INVERSION EVENTUELLE DES coordonnees
py = pix2.y;
dx = pix1.x - pix2.x;
dy = pix1.y - pix2.y;
incr_e = 2 * dy;
incr_ne = 2 * (dy -dx);

px = pix2;
while (px.x <= pix1.x)
{
* Debut Allumage du pixel*
if (px.z == 0)
px.color = mlx_get_color_value(infos->mlx, 0x00FFFFFF);
else
px.color = mlx_get_color_value(infos->mlx, 0x00FF0000 / abs(px.z));
infos->img_data[px.y * infos->size_line + px.x * ((infos->bpp) / 8)] = px.color;
px.x++;
*Fin Allumage du pixel*
if (err >= 0)
{
py += 1;
err += incr_ne;
}
else
err += incr_e;
}

}*/
