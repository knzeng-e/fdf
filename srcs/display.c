#include "get_map.h"

void	zoom_in(t_infos *infos)
{	
	infos->zoom_x += 1;
	infos->zoom_y += 1;
	expose_hook(infos);
}

void	zoom_out(t_infos *infos)
{	
	if ((infos->zoom_x - 1 > 0) && (infos->zoom_y - 1 > 0))
	{
		infos->zoom_x -= 1;
		infos->zoom_y -= 1;
		expose_hook(infos);
	}
}

void	quit(t_infos *infos)
{	
	mlx_destroy_image(infos->mlx, infos->ptr_img);
	exit (0);
}

void	switch_view_isometric(t_infos *infos)
{
	if (infos->view == PARALLEL)
	{
		infos->view = ISOMETRIC;
		expose_hook(infos);
	}
}

void	switch_view_parallel(t_infos *infos)
{
	if (infos->view == ISOMETRIC)
	{
		infos->view = PARALLEL;
		expose_hook(infos);
	}
}
