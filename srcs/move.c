#include "get_map.h"

void	move_left(t_infos *infos)
{
	infos->x_orig -= SPEED;
	expose_hook(infos);
}

void	move_right(t_infos *infos)
{
	infos->x_orig += SPEED;
	expose_hook(infos);
}

void	move_up(t_infos *infos)
{	
	infos->y_orig -= SPEED;
	expose_hook(infos);
}

void	move_down(t_infos *infos)
{
	infos->y_orig += SPEED;
	expose_hook(infos);
}
