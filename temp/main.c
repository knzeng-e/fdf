#include "mlx.h"
#include <unistd.h>

int	main()
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	mlx = mlx_init();
	x = 50;
	win = mlx_new_window(mlx, 400, 400, "MLX 42");
	while (x < 150)
	{
		y = 50;
		while (y < 150)
		{
			mlx_pixel_put(mlx, win, x, y, 0XFF0000);
			y++;
		}
		x++;
	}
	mlx_loop(mlx);
}
