#include "../../includes/cub3d.h"

int	check_walls(int width, int index, char **map)
{
	int	i;

	i = 0;
	while (map[index][i] == '0' || map[index][i] == '1'
		|| map[index][i] == 'N' || map[index][i] == 'S'
		|| map[index][i] == 'E' || map[index][i] == 'W'
		|| map[index][i] == ' ')
		i++;
	if (i == width && map[index][i - 1] == '1')
		return (TRUE);
	else
		return (FALSE);
}
