#include "../../includes/cub3d.h"

int	map_check(t_game_data *game)
{
	if (check_lines(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_lines(t_game_data *game)
{
	int	index;
	int	width;

	index = 0;
	while (game->map[index])
	{
		width = map_width(index, game->map);
		if (check_walls(width, index, game->map) == FALSE)
			return (FALSE);
		index++;
	}
	if (check_start(game) == FALSE)
		return (FALSE);
	if (check_filling(game) == FALSE)
		return (FALSE);
	game->map_width = get_map_width(game->map);
	game->map_height = get_map_height(game->map);
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
		return (close(fd), FALSE);
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

	if (!*s)
		return ;
	index = 0;
	while (s[index])
	{
		free(s[index]);
		index++;
	}
	free(s);
}
