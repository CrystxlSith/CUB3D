/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:34:27 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_first_or_last_line(int i, t_game_data *game)
{
	int	y;

	y = 0;
	while (game->map[i][y])
	{
		if (game->map[i][y] != '1' && game->map[i][y] != ' ')
			return (FALSE);
		if (check_spaces(game, i, y) == -1)
			return (FALSE);
		y++;
	}
	return (TRUE);
}

int	check_inner_line(int i, t_game_data *game)
{
	int	y;

	y = 0;
	while (game->map[i][y] == ' ')
		y++;
	if (game->map[i][y] != '1')
		return (FALSE);
	while (game->map[i][y])
	{
		if (i > 0 && game->map[i][y] == ' ' && game->map[i - 1][y] == '0')
			return (FALSE);
		y++;
	}
	y--;
	if (i != 0)
	{
		while (y >= 0 && game->map[i][y] == ' ' &&
			(game->map[i - 1][y] == '1' || game->map[i - 1][y] == ' '))
			y--;
	}
	if (game->map[i][y] != '1')
		return (FALSE);
	return (TRUE);
}

int	is_line_closed(int i, t_game_data *game, int length)
{
	if (i == 0 || i == length)
		return (check_first_or_last_line(i, game));
	return (check_inner_line(i, game));
}

int	is_map_closed(t_game_data *game, int length)
{
	int	y;

	if (!game->map || length <= 0)
		return (FALSE);
	y = 0;
	while (y < length)
	{
		if (!is_line_closed(y, game, length))
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
