#include "../../includes/cub3d.h"

int	check_start(char **map)
{
	int	index_x;
	int	index_y;
	int	count;

	index_x = 0;
	index_y = 0;
	count = 0;
	while (map[index_x])
	{
		index_y = 0;
		while (map[index_x][index_y])
		{
			if (map[index_x][index_y] == 'N' || map[index_x][index_y] == 'S'
				|| map[index_x][index_y] == 'E' || map[index_x][index_y] == 'W')
				count++;
			index_y++;
		}
		index_x++;
	}
	if (count == 0)
		return (FALSE);
	if (count > 1)
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
