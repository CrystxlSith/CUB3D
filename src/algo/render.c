/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:58:00 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/12/18 15:50:49 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	strafe_left(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x - game->raycast.diry * new_speed;
	newposy = game->player.y + game->raycast.dirx * new_speed;
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

static void	strafe_right(t_game_data *game, double movespeed)
{
	double	newposx;
	double	newposy;
	double	new_speed;

	new_speed = game->raycast.delta_time * movespeed * 60.0;
	newposx = game->player.x + game->raycast.diry * new_speed;
	newposy = game->player.y - game->raycast.dirx * new_speed;
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

void	update_player(t_game_data *game)
{
	if (game->key.escape)
		exit_error(game, "Exit game\n");
	else if (game->key.forward == 1)
		move_front(game, game->movespeed);
	else if (game->key.backward == 1)
		move_back(game, game->movespeed);
	else if (game->key.turn_left == 1)
		turn_left(game, game->rotspeed);
	else if (game->key.turn_right == 1)
		turn_right(game, game->rotspeed);
	else if (game->key.strafe_left == 1)
		strafe_left(game, game->movespeed);
	else if (game->key.strafe_right == 1)
		strafe_right(game, game->movespeed);
}

int	render_frame(t_game_data *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_player(game);
	draw_floor_and_ceiling(game);
	floorcasting(game);
	raycasting(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img, 0, 0);
	fps_count(game);
	return (0);
}
