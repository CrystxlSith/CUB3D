#include "../../includes/cub3d.h"

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map[height] != NULL)
		height++;
	return (height);
}

int	get_map_width(char **map)
{
	int	width;

	width = 0;
	if (map[0] != NULL)
		width = ft_strlen(map[0]);
	return (width);
}

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

int	check_filling(t_game_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == '1' || game->map[x][y] == '0'
				|| game->map[x][y] == 'N' || game->map[x][y] == 'S'
				|| game->map[x][y] == 'E' || game->map[x][y] == 'W'
				|| game->map[x][y] == ' ' || game->map[x][y] == 'P')
				y++;
			else
				return (FALSE);
		}
		x++;
	}
	return (TRUE);
}
