#include "../../includes/cub3d.h"

void	turn_right(t_game_data *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->raycast.dirx;
	game->raycast.dirx = game->raycast.dirx * cos(-rotation_speed) - \
	game->raycast.diry * sin(-rotation_speed);
	game->raycast.diry = old_dirx * sin(-rotation_speed) + \
	game->raycast.diry * cos(-rotation_speed);
	old_planex = game->raycast.planex;
	game->raycast.planex = game->raycast.planex * cos(-rotation_speed) - \
	game->raycast.planey * sin(-rotation_speed);
	game->raycast.planey = old_planex * sin(-rotation_speed) + \
	game->raycast.planey * cos(-rotation_speed);
}

void	turn_left(t_game_data *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->raycast.dirx;
	game->raycast.dirx = game->raycast.dirx * cos(rotation_speed) - \
	game->raycast.diry * sin(rotation_speed);
	game->raycast.diry = old_dirx * sin(rotation_speed) + \
	game->raycast.diry * cos(rotation_speed);
	old_planex = game->raycast.planex;
	game->raycast.planex = game->raycast.planex * cos(rotation_speed) - \
	game->raycast.planey * sin(rotation_speed);
	game->raycast.planey = old_planex * sin(rotation_speed) + \
	game->raycast.planey * cos(rotation_speed);
}

void	move_front(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x + game->raycast.dirx * new_speed;
	newposy = game->player.y + game->raycast.diry * new_speed;
	if (game->map[(int)newposx][(int)game->player.y] != '1')
	{
		game->player.x = newposx;
		game->raycast.posx = newposx;
	}
	if (game->map[(int)game->player.x][(int)newposy] != '1')
	{
		game->player.y = newposy;
		game->raycast.posy = newposy;
	}
}

void	move_back(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x - game->raycast.dirx * new_speed;
	newposy = game->player.y - game->raycast.diry * new_speed;
	if (game->map[(int)newposx][(int)game->player.y] != '1')
	{
		game->player.x = newposx;
		game->raycast.posx = newposx;
	}
	if (game->map[(int)game->player.x][(int)newposy] != '1')
	{
		game->player.y = newposy;
		game->raycast.posy = newposy;
	}
}
