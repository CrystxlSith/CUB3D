#include "../../includes/cub3d.h"

void	set_index(int index_x, int index_y, t_game_data *game)
{
	game->player.x = index_x + 0.5;
	game->player.y = index_y + 0.5;
	game->raycast.posx = index_x + 0.5;
	game->raycast.posy = index_y + 0.5;
}

int	check_start(t_game_data *game)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == 'N' || game->map[x][y] == 'S'
				|| game->map[x][y] == 'E' || game->map[x][y] == 'W')
			{
				set_index(x, y, game);
				count++;
			}
			y++;
		}
		x++;
	}
	if (count == 0 || count > 1)
		return (FALSE);
	return (TRUE);
}

int	check_filling(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '1' || map[x][y] == '0'
				|| map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W'
				|| map[x][y] == ' ')
				y++;
			else
				return (FALSE);
		}
		x++;
	}
	return (TRUE);
}
