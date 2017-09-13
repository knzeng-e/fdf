#include "get_map.h"

void	set_dx_values(t_infos *infos)
{
	if (infos->dx >= 0)
	{
		infos->x = infos->x1;
		infos->y = infos->y1;
		infos->xe = infos->x2;
	}
	else
	{
		infos->x = infos->x2;
		infos->y = infos->y2;
		infos->xe = infos->x1;
	}
}

void	set_dy_values(t_infos *infos)
{
	if (infos->dy >= 0)
	{
		infos->x = infos->x1;
		infos->y = infos->y1;
		infos->ye = infos->y2;
	}
	else
	{
		infos->x = infos->x2;
		infos->y = infos->y2;
		infos->ye = infos->y1;
	}
}

void	set_values(t_infos *infos, char *d_variable)
{
	if (ft_strcmp(d_variable, "dx") == 0)
		set_dx_values(infos);
	else
		set_dy_values(infos);
}
