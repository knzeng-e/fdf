#include "get_map.h"

void	increase_height(t_infos *infos)
{
	infos->zoom_y += 1;
	expose_hook(infos);
}

void	decrease_height(t_infos *infos)
{
	if (infos->zoom_y - 1 > 0)
	{
		infos->zoom_y--;
		expose_hook(infos);
	}
}

void	increase_width(t_infos *infos)
{
	infos->zoom_x++;
	expose_hook(infos);
}

void	decrease_width(t_infos *infos)
{
	if (infos->zoom_x - 1 > 0)
	{
		infos->zoom_x--;
		expose_hook(infos);
	}
}
