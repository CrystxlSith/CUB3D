/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:17 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_position(t_game_data *game, double new_x, double new_y)
{
	if (new_x < 0 || new_y >= game->map_width || new_y < 0 || \
	new_x >= game->map_height)
		return (0);
	if (game->map[(int)new_x][(int)new_y] == '1')
		return (0);
	if (game->map[(int)new_x][(int)new_y] == 'P')
		return (0);
	return (1);
}

void	turn_right(t_game_data *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->raycast.dirx;
	game->raycast.dirx = game->raycast.dirx * cos(-rotation_speed) - \
	game->raycast.diry * sin(-rotation_speed);
	game->raycast.diry = old_dirx * sin(-rotation_speed) + \
	game->raycast.diry * cos(-rotation_speed);
	old_planex = game->raycast.planex;
	game->raycast.planex = game->raycast.planex * cos(-rotation_speed) - \
	game->raycast.planey * sin(-rotation_speed);
	game->raycast.planey = old_planex * sin(-rotation_speed) + \
	game->raycast.planey * cos(-rotation_speed);
}

void	turn_left(t_game_data *game, double rotation_speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->raycast.dirx;
	game->raycast.dirx = game->raycast.dirx * cos(rotation_speed) - \
	game->raycast.diry * sin(rotation_speed);
	game->raycast.diry = old_dirx * sin(rotation_speed) + \
	game->raycast.diry * cos(rotation_speed);
	old_planex = game->raycast.planex;
	game->raycast.planex = game->raycast.planex * cos(rotation_speed) - \
	game->raycast.planey * sin(rotation_speed);
	game->raycast.planey = old_planex * sin(rotation_speed) + \
	game->raycast.planey * cos(rotation_speed);
}

void	move_front(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x + game->raycast.dirx * new_speed;
	newposy = game->player.y + game->raycast.diry * new_speed;
	if (is_valid_position(game, newposx, game->player.y))
	{
		game->player.x = newposx;
		game->raycast.posx = newposx;
	}
	if (is_valid_position(game, game->player.x, newposy))
	{
		game->player.y = newposy;
		game->raycast.posy = newposy;
	}
}

void	move_back(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x - game->raycast.dirx * new_speed;
	newposy = game->player.y - game->raycast.diry * new_speed;
	if (is_valid_position(game, newposx, game->player.y))
	{
		game->player.x = newposx;
		game->raycast.posx = newposx;
	}
	if (is_valid_position(game, game->player.x, newposy))
	{
		game->player.y = newposy;
		game->raycast.posy = newposy;
	}
}
