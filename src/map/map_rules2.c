/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rules2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:34:32 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_index2(t_game_data *game, char c)
{
	if (c == 'E')
	{
		game->raycast.dirx = 0;
		game->raycast.diry = 1;
		game->raycast.planex = 0.66;
		game->raycast.planey = 0;
	}
	else if (c == 'W')
	{
		game->raycast.dirx = 0;
		game->raycast.diry = -1;
		game->raycast.planex = -0.66;
		game->raycast.planey = 0;
	}
}

void	set_index(int index_x, int index_y, t_game_data *game, char c)
{
	game->player.x = index_x + 0.5;
	game->player.y = index_y + 0.5;
	game->raycast.posx = index_x + 0.5;
	game->raycast.posy = index_y + 0.5;
	if (c == 'N')
	{
		game->raycast.dirx = -1;
		game->raycast.diry = 0;
		game->raycast.planex = 0;
		game->raycast.planey = 0.66;
	}
	else if (c == 'S')
	{
		game->raycast.dirx = 1;
		game->raycast.diry = 0;
		game->raycast.planex = 0;
		game->raycast.planey = -0.66;
	}
	else
		set_index2(game, c);
}

int	check_start(t_game_data *game)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	y = 0;
	count = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == 'N' || game->map[x][y] == 'S'
				|| game->map[x][y] == 'E' || game->map[x][y] == 'W')
			{
				set_index(x, y, game, game->map[x][y]);
				count++;
			}
			y++;
		}
		x++;
	}
	if (count == 0 || count > 1)
		return (FALSE);
	return (TRUE);
}

int	check_spaces(t_game_data *game, int x, int y)
{
	if (game->map[x][y] == ' ' && x > 0
		&& y > 0 && x < game->map_height - 1 && y < game->map_width - 1)
	{
		if (game->map[x + 1][y] == '0' || game->map[x - 1][y] == '0'
			|| game->map[x][y + 1] == '0' || game->map[x][y - 1] == '0')
			return (-1);
		if (game->map[x + 1][y] == 'P' || game->map[x - 1][y] == 'P'
			|| game->map[x][y + 1] == 'P' || game->map[x][y - 1] == 'P')
			return (-1);
	}
	return (0);
}

int	check_filling(t_game_data *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map[x])
	{
		y = 0;
		while (game->map[x][y])
		{
			if (game->map[x][y] == '1' || game->map[x][y] == '0'
				|| game->map[x][y] == 'N' || game->map[x][y] == 'S'
				|| game->map[x][y] == 'E' || game->map[x][y] == 'W'
				|| game->map[x][y] == ' ' || game->map[x][y] == 'P')
			{
				if (check_spaces(game, x, y) == -1)
					return (FALSE);
				y++;
			}
			else
				return (FALSE);
		}
		x++;
	}
	return (TRUE);
}
