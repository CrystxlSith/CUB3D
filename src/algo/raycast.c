#include "../../includes/cub3d.h"

void	texture_number(t_game_data *game)
{
	if (game->raycast.is_door)
	{
		game->raycast.texnum = 4;
	}
	else
	{
		if (game->raycast.side == 0)
		{
			if (game->raycast.raydirx > 0)
				game->raycast.texnum = 0;
			else
				game->raycast.texnum = 1;
		}
		else
		{
			if (game->raycast.raydiry > 0)
				game->raycast.texnum = 2;
			else
				game->raycast.texnum = 3;
		}
	}
}

void	texture_calculation(t_game_data *game)
{
	if (game->raycast.side == 0)
		game->raycast.wallx = game->raycast.posy + \
			game->raycast.perpwalldist * game->raycast.raydiry;
	else
		game->raycast.wallx = game->raycast.posx + \
			game->raycast.perpwalldist * game->raycast.raydirx;
	game->raycast.wallx -= floor(game->raycast.wallx);
	game->raycast.texx = (int)(game->raycast.wallx * \
		(double)game->textures[game->raycast.texnum].width);
	if (game->raycast.side == 0 && game->raycast.raydirx > 0)
		game->raycast.texx = game->textures[game->raycast.texnum].width \
			- game->raycast.texx - 1;
	if (game->raycast.side == 1 && game->raycast.raydiry < 0)
		game->raycast.texx = game->textures[game->raycast.texnum].width \
			- game->raycast.texx - 1;
}

void	step_dist(t_game_data *game)
{
	if (game->raycast.raydirx < 0)
	{
		game->raycast.stepx = -1;
		game->raycast.sidedistx = (game->raycast.posx - game->player.mapx) \
			* game->raycast.deltadistx;
	}
	else
	{
		game->raycast.stepx = 1;
		game->raycast.sidedistx = (game->player.mapx + 1.0 - \
			game->raycast.posx) * game->raycast.deltadistx;
	}
	if (game->raycast.raydiry < 0)
	{
		game->raycast.stepy = -1;
		game->raycast.sidedisty = (game->raycast.posy - \
			game->player.mapy) * game->raycast.deltadisty;
	}
	else
	{
		game->raycast.stepy = 1;
		game->raycast.sidedisty = (game->player.mapy + 1.0 - \
			game->raycast.posy) * game->raycast.deltadisty;
	}
}

void	raycalculate(t_game_data *game, int x)
{
	game->raycast.is_door = 0;
	game->player.mapx = (int)game->player.x;
	game->player.mapy = (int)game->player.y;
		game->raycast.deltadistx = fabs(1 / game->raycast.raydirx);
	if (game->raycast.raydiry == 0)
		game->raycast.deltadisty = 1e30;
	else
		game->raycast.deltadisty = fabs(1 / game->raycast.raydiry);
	step_dist(game);
	digital_differential_analyzer(game);
	perp_wall_dist(game);
	texture_number(game);
	texture_calculation(game);
	draw_raycast(game, x);
}

void	raycasting(t_game_data *game)
{
	int		i;
	double	camerax;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		camerax = 2 * i / (double)SCREEN_WIDTH - 1;
		game->raycast.raydirx = game->raycast.dirx + \
			game->raycast.planex * camerax;
		game->raycast.raydiry = game->raycast.diry + \
			game->raycast.planey * camerax;
		raycalculate(game, i);
		i++;
	}
}
