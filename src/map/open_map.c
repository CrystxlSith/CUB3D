#include "../../includes/cub3d.h"

int	fill_map_struct(t_game_data *game, char **av)
{
	char	*full_file;
	int		index;

	game->file = NULL;
	game->map = NULL;
	full_file = open_file(av[1], ".cub");
	if (!full_file)
		return (close_mlx(game), exit(EXIT_FAILURE), -1);
	game->file = ft_split(full_file, '\n');
	free(full_file);
	if (!game->file)
		return (-1);
	init_game(game);
	if (get_textures(game, game->file) == -1)
		return (-1);
	index = get_map_index(game->file);
	if (index == -1)
		return (-1);
	game->map = get_map(game->file, index);
	if (!game->map)
		return (-1);
	complete_map(game);
	if (map_check(game) == FALSE)
		return (-1);
	return (0);
}

char	*open_file(char *av, char *extension)
{
	char	*full_file;
	int		fd;
	int		ret;
	int		size;
	char	*final_file;

	if (check_file(av, extension) == FALSE)
		return (NULL);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (NULL);
	size = count_lines(fd);
	close(fd);
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (NULL);
	full_file = ft_calloc(size + 1, sizeof(char));
	ret = read(fd, full_file, size);
	if (ret == -1)
		return (free(full_file), close(fd), NULL);
	final_file = ft_strdup(full_file);
	return (free(full_file), close(fd), final_file);
}

int	get_map_index(char **file)
{
	int	index;
	int	i;

	index = 0;
	i = 0;
	if (!file)
		return (-1);
	while (file[index])
	{
		while (file[index][i] != ' ' && file[index][i] != '1')
			index++;
		if (file[index][i] == ' ' || file[index][i] == '1')
		{
			i = 0;
			while (file[index][i])
			{
				if (file[index][i] == '1')
					return (index);
				i++;
			}
		}
		if (file[index + 1])
			index++;
	}
	return (-1);
}

int	count_lines_map(char **file, int index)
{
	int	count;

	count = 0;
	while (file[index + count])
		count++;
	return (count);
}

char	**get_map(char **file, int index)
{
	int		size;
	char	**map;
	int		i;

	i = 0;
	size = count_lines_map(file, index);
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		return (NULL);
	while (file[index + i])
	{
		map[i] = ft_strdup(file[index + i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}
