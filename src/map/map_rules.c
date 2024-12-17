#include "../../includes/cub3d.h"

int	check_walls(int width, int index, char **map)
{
	int	i;

	i = 0;
	if (index == 0 || map[index + 1] == NULL)
	{
		while (map[index][i] == ' ' || map[index][i] == '1')
			i++;
	}
	else
	{
		while (map[index][i] == '0' || map[index][i] == '1'
			|| map[index][i] == 'N' || map[index][i] == 'S'
			|| map[index][i] == 'E' || map[index][i] == 'W'
			|| map[index][i] == ' ' || map[index][i] == 'P')
			i++;
	}
	if (i == width && map[index][i - 1] == '1')
		return (TRUE);
	else
		return (FALSE);
}
