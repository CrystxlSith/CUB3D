#include "../includes/cub3d.h"

int	map_check(char **input)
{
	if (check_lines(input) == FALSE)
		return (FALSE);
	// if (!flood_fill(input))
	// 	return (FALSE);
	return (TRUE);
}

int	check_lines(char **map)
{
	int	index;
	int	width;

	index = 0;
	while (map[index])
	{
		width = map_width(index, map);
		if (check_walls(width, index, map) == FALSE)
			return (ft_putstr_fd("Error\nWall Error\n", 2), FALSE);
		index++;
	}
	if (check_start(map) == FALSE)
		return (ft_putstr_fd("Error\nStart Error\n", 2), FALSE);
	if (check_filling(map) == FALSE)
		return (ft_putstr_fd("Error\nFilling Error\n", 2), FALSE);
	return (TRUE);
}

int	count_lines(int fd)
{
	int		count;
	char	map_name[4096];
	int		ret;

	count = 0;
	ret = read(fd, map_name, sizeof(map_name));
	if (ret == -1)
		return (close(fd), \
			ft_printf("Error\n Read Map%s\n"), FALSE);
	count = ret;
	return (count);
}

int	check_file(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	i = i - 4;
	if (ft_strncmp(&input[i], ".cub", 5) == 0)
		return (TRUE);
	return (FALSE);
}

void	free_everything(char **s)
{
	int	index;

	index = 0;
	while (s[index])
	{
		free(s[index]);
		index++;
	}
	free(s);
}
