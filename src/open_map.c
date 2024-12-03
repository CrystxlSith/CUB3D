#include "../includes/cub3d.h"

int	fill_map_struct(t_game_data *game, char **av)
{
	char	*full_file;
	int		index;

	game->file = NULL;
	full_file = open_file(av);
	if (!full_file)
		return (-1);
	game->file = ft_split(full_file, '\n');
	free(full_file);
	if (!game->file)
		return (-1);
	index = get_map_index(game->file);
	if (index == -1)
		return (free_everything(game->file), -1);
	game->map = get_map(game->file, index);
	index = 0;
	if (!game->map)
		return (free_everything(game->file), -1);
	if (map_check(game->map) == FALSE)
		return (free_everything(game->map), free_everything(game->file), -1);
	init_game(game);
	exit(0);
}

char	*open_file(char **av)
{
	char	*full_file;
	int		fd;
	int		ret;
	int		size;
	char	*final_file;

	if (check_file(av[1]) == FALSE)
		return (ft_putstr_fd("Error\nWrong File\n", 2), NULL);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nOpen file\n", 2), NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_putstr_fd("Error\nWrong input\n", 2), NULL);
	size = count_lines(fd);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nOpen file\n", 2), NULL);
	full_file = ft_calloc(size + 1, sizeof(char));
	ret = read(fd, full_file, size);
	if (ret == -1)
		return (free(full_file), close(fd), \
			ft_putstr_fd("Error\nRead file\n", 2), NULL);
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
		if (file[index][i] == ' ')
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
