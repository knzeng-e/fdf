#include "get_map.h"


void	drawpixel_dx()
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
	putpixel(mlx, win, x, y, c);
	while (x < xe)
	{
		x = x + 1;
		if (px < 0)
			px = px + 2 * dy1;
		else
		{
			y = (((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) ? ++y : --y);
			px = px + 2 * (dy1 - dx1);
		}
		putpixel(mlx, win, x, y, c);
	}
}

void	draw_pixel_dy()
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
	putpixel(mlx, win, x, y, c);
	while (y < ye)
	{
		y++;
		if (py <= 0)
			py = py + 2 * dx1;
		else
		{
			x = (((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) ? ++x : --x);
			py = py + 2 * (dx1 - dy1);
		}
		putpixel(mlx, win, x, y, c);
	}
}

void	putpixel(void *mlx, void *win, int x, int y, int color)
{
	mlx_pixel_put(mlx, win, x, y, color);
}

void	bhm_line(void *mlx, void *win, int x1, int y1, int x2, int y2, int c)
{
	int x,y,dx,dy,dx1,dy1,px,py,xe,ye;

	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = abs(dx);
	dy1 = abs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
		draw_pixel_dx();
	else
	{
		draw_pixel_dy();
	}
}


int main()
{
	int	*mlx;
	int	*win;
	int	x;
	int	y;


	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 300, "Essai segment");

	x = 0;
	while (x < 400)
	{
		y = 0;
		while (y < 300)
		{
			bhm_line(mlx, win, 200, 150, x, y, 0x00FFFFFF / (x + 0.5));
			y += 10;
		}
		x += 10;
	}
	mlx_loop(mlx);
	return (0);
}
