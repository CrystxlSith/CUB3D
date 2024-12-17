#include "../../includes/cub3d.h"

static void	fill(t_game_data *game, int max_len, int i, char **new_map)
{
	int	j;

	while (game->map[i])
	{
		new_map[i] = ft_calloc(max_len + 1, sizeof(char));
		j = 0;
		while (game->map[i][j])
		{
			new_map[i][j] = game->map[i][j];
			j++;
		}
		while (j < max_len)
		{
			new_map[i][j] = ' ';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
}

void	complete_map(t_game_data *game)
{
	int		max_len;
	int		i;
	char	**new_map;

	max_len = 0;
	i = 0;
	while (game->map[i])
	{
		if (ft_strlen(game->map[i]) > (size_t)max_len)
			max_len = ft_strlen(game->map[i]);
		i++;
	}
	new_map = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	fill(game, max_len, i, new_map);
	free_everything(game->map);
	game->map = new_map;
}
