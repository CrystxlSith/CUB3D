#include "../../includes/cub3d.h"

void	set_index(int index_x, int index_y, t_game_data *game)
{
	game->player.x = index_x + 0.5;
	game->player.y = index_y + 0.5;
	game->raycast.posx = index_x + 0.5;
	game->raycast.posy = index_y + 0.5;
}

void	start_condition(int count, int index_x, int index_y, t_game_data *game)
{
	if (game->map[index_x][index_y] == 'N'
		|| game->map[index_x][index_y] == 'S'
		|| game->map[index_x][index_y] == 'E'
		|| game->map[index_x][index_y] == 'W')
	{
		set_index(index_x, index_y, game);
		count++;
	}
}

int	check_start(t_game_data *game)
{
	int	index_x;
	int	index_y;
	int	count;

	index_x = 0;
	index_y = 0;
	count = 0;
	while (game->map[index_x])
	{
		index_y = 0;
		while (game->map[index_x][index_y])
		{
			start_condition(count, index_x, index_y, game);
			index_y++;
		}
		index_x++;
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
