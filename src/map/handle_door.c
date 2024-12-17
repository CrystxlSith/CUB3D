#include "../../includes/cub3d.h"

void	init_doors(t_game_data *game)
{
	int	x;
	int	y;

	game->door_nbr = 0;
	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == 'P')
			{
				game->doors[game->door_nbr].x = x;
				game->doors[game->door_nbr].y = y;
				game->doors[game->door_nbr].state = 0;
				game->door_nbr++;
			}
			y++;
		}
		x++;
	}
}

void	handle_door(t_game_data *game)
{
	int	i;

	i = -1;
	while (++i < game->door_nbr)
	{
		if ((game->doors[i].x == game->player.mapx
				|| game->doors[i].x == game->player.mapx - 1
				|| game->doors[i].x == game->player.mapx + 1)
			&& (game->doors[i].y == game->player.mapy
				|| game->doors[i].y == game->player.mapy - 1
				|| game->doors[i].y == game->player.mapy + 1))
		{
			if (game->doors[i].state == 0)
			{
				game->map[game->doors[i].x][game->doors[i].y] = '2';
				game->doors[i].state = 1;
			}
			else if (game->doors[i].state == 1)
			{
				game->map[game->doors[i].x][game->doors[i].y] = 'P';
				game->doors[i].state = 0;
			}
			break ;
		}
	}
}
