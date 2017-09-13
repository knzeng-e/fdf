#include "get_map.h"

static void	init_aspect_functions(t_key_functions *functions)
{
	functions->s_increase_height.keycode = 13;
	functions->s_increase_height.func = increase_height;
	functions->s_increase_width.keycode = 2;
	functions->s_increase_width.func = increase_width;
	functions->s_decrease_height.keycode = 1;
	functions->s_decrease_height.func = decrease_height;
	functions->s_decrease_width.keycode = 0;
	functions->s_decrease_width.func = decrease_width;
}

static void	init_move_functions(t_key_functions *functions)
{
	functions->s_move_left.keycode = 123;
	functions->s_move_left.func = move_left;
	functions->s_move_right.keycode = 124;
	functions->s_move_right.func = move_right;
	functions->s_move_up.keycode = 126;
	functions->s_move_up.func = move_up;
	functions->s_move_down.keycode = 125;
	functions->s_move_down.func = move_down;
}

static void	init_view_functions(t_key_functions *functions)
{
	functions->s_zoom_in.keycode = 44;
	functions->s_zoom_in.func = zoom_in;
	functions->s_zoom_out.keycode = 24;
	functions->s_zoom_out.func = zoom_out;
	functions->s_switch_view_isometric.keycode = 34;
	functions->s_switch_view_isometric.func = switch_view_isometric;
	functions->s_switch_view_parallel.keycode = 35;
	functions->s_switch_view_parallel.func = switch_view_parallel;
}

static void	init_functions(t_key_functions *functions)
{
	init_aspect_functions(functions);
	init_move_functions(functions);
	init_view_functions(functions);
	functions->s_quit.keycode = 53;
	functions->s_quit.func = quit;
}

void	set_functions(t_function *tab_func)
{
	t_key_functions	*functions;

	functions = (t_key_functions *)malloc(sizeof(t_key_functions));
	if (!functions)
		exit(-9);
	init_functions(functions);
	tab_func[0] = functions->s_increase_height;
	tab_func[1] = functions->s_increase_width;
	tab_func[2] = functions->s_decrease_height;
	tab_func[3] = functions->s_decrease_width;
	tab_func[4] = functions->s_move_left;
	tab_func[5] = functions->s_move_right;
	tab_func[6] = functions->s_move_up;
	tab_func[7] = functions->s_move_down;
	tab_func[8] = functions->s_zoom_in;
	tab_func[9] = functions->s_zoom_out;
	tab_func[10] = functions->s_quit;
	tab_func[11] = functions->s_switch_view_isometric;
	tab_func[12] = functions->s_switch_view_parallel;
}
