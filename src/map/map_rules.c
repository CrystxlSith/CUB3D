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

int	check_texture_files(char *texture)
{
	char	*file;
	char	**final_file;
	int		i;
	char	**line;

	i = 0;
	file = open_file(texture, ".xpm");
	if (!file)
		return (-1);
	final_file = ft_split(file, '\n');
	free(file);
	if (!final_file)
		return (-1);
	line = ft_split(final_file[3], ' ');
	free_everything(final_file);
	if (!line)
		return (-1);
	while (line[i])
		i++;
	if (i != 5)
		return (free_everything(line), -1);
	return (free_everything(line), 0);
}

int	texture_verify(t_game_data *game)
{
	(void)game;
	if (check_texture_files("textures/dark_oak_trapdoor.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/obsidian.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/suspicious_gravel_0.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/polished_blackstone_bricks_0.xpm") \
		== -1)
		return (-1);
	if (check_texture_files("textures/tuff.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/dragon_egg.xpm") == -1)
		return (-1);
	if (check_texture_files("textures/black_terracotta.xpm") == -1)
		return (-1);
	return (0);
}
