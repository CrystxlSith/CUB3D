#include "../../includes/cub3d.h"

int	is_line_closed(int i, char **map, int length)
{
	int	y;

	y = 0;
	(void)length;
	while (map[i][y] == ' ')
		y++;
	if (map[i][y] != '1')
		return (FALSE);
	while (map[i][y])
	{
		if (i > 0 && map[i][y] == ' ' && map[i - 1][y] == '0')
			return (FALSE);
		y++;
	}
	y--;
	if (i != 0)
	{
		while (y >= 0 && map[i][y] == ' '
			&& (map[i - 1][y] == '1' || map[i - 1][y] == ' '))
			y--;
	}
	if (map[i][y] != '1')
		return (FALSE);
	return (TRUE);
}

int	is_map_closed(char **map, int length)
{
	int	y;

	if (!map || length <= 0)
		return (FALSE);
	y = 0;
	while (y < length)
	{
		if (!is_line_closed(y, map, length))
			return (FALSE);
		y++;
	}
	return (TRUE);
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
