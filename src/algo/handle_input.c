#include "../../includes/cub3d.h"

int	handle_input(int keycode, t_game_data *game)
{
	if (keycode == XK_Escape)
		game->key.escape = 1;
	else if (keycode == XK_w)
		game->key.forward = 1;
	else if (keycode == XK_s)
		game->key.backward = 1;
	else if (keycode == XK_a)
		game->key.turn_left = 1;
	else if (keycode == XK_d)
		game->key.turn_right = 1;
	else if (keycode == XK_e && game->key_e_pressed == 0)
	{
		game->key_e_pressed = 1;
		handle_door(game);
	}
	return (0);
}

int	input_release(int keycode, t_game_data *game)
{
	if (keycode == XK_w)
		game->key.forward = 0;
	else if (keycode == XK_s)
		game->key.backward = 0;
	else if (keycode == XK_a)
		game->key.turn_left = 0;
	else if (keycode == XK_d)
		game->key.turn_right = 0;
	else if (keycode == XK_e)
		game->key_e_pressed = 0;
	return (0);
}

int	close_game(t_game_data *game)
{
	exit_error(game, "Exit game\n");
	return (0);
}

int	handle_mouse_motion(int x, int y, t_game_data *game)
{
	static int	last_x;
	int			delta_x;
	double		rotation_speed;
	double		old_dir_x;
	double		old_plane_x;

	(void)y;
	delta_x = x - last_x;
	last_x = x;
	rotation_speed = 0.003;
	old_dir_x = game->raycast.dirx;
	game->raycast.dirx = game->raycast.dirx * cos(-delta_x * rotation_speed) \
		- game->raycast.diry * sin(-delta_x * rotation_speed);
	game->raycast.diry = old_dir_x * sin(-delta_x * rotation_speed) \
		+ game->raycast.diry * cos(-delta_x * rotation_speed);
	old_plane_x = game->raycast.planex;
	game->raycast.planex = game->raycast.planex * cos(-delta_x * \
		rotation_speed) - game->raycast.planey * sin(-delta_x * rotation_speed);
	game->raycast.planey = old_plane_x * sin(-delta_x * rotation_speed) \
		+ game->raycast.planey * cos(-delta_x * rotation_speed);
	return (0);
}
