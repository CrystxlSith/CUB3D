/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:32:04 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	verline(t_game_data *game, int x, int start, int end)
{
	int	color;

	while (start <= end)
	{
		game->raycast.texy = (((start * 2 - SCREEN_HEIGHT + \
			game->raycast.line_height) * \
			game->textures[game->raycast.texnum].height) / \
			game->raycast.line_height) / 2;
		color = *(int *)(game->textures[game->raycast.texnum].addr + \
			(game->raycast.texy * \
			game->textures[game->raycast.texnum].line_length \
			+ game->raycast.texx * \
			(game->textures[game->raycast.texnum].bpp / 8)));
		my_mlx_pixel_put(game, x, start, color);
		start++;
	}
}

void	draw_raycast(t_game_data *game, int x)
{
	int	draw_start;
	int	draw_end;

	game->raycast.line_height = (int)(SCREEN_HEIGHT / \
		game->raycast.perpwalldist);
	draw_start = -game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	verline(game, x, draw_start, draw_end);
}

static void	update_ray(t_game_data *game)
{
	if (game->raycast.sidedistx < game->raycast.sidedisty)
	{
		game->raycast.sidedistx += game->raycast.deltadistx;
		game->player.mapx += game->raycast.stepx;
		game->raycast.side = 0;
	}
	else
	{
		game->raycast.sidedisty += game->raycast.deltadisty;
		game->player.mapy += game->raycast.stepy;
		game->raycast.side = 1;
	}
}

void	digital_differential_analyzer(t_game_data *game)
{
	game->raycast.hit = 0;
	while (game->raycast.hit == 0)
	{
		update_ray(game);
		if (game->player.mapx < 0 || game->player.mapy >= game->map_width || \
		game->player.mapy < 0 || game->player.mapx >= game->map_height)
			break ;
		if (game->map[game->player.mapx][game->player.mapy] == '1')
		{
			game->raycast.hit = 1;
			game->raycast.is_door = 0;
		}
		else if (game->map[game->player.mapx][game->player.mapy] == 'P')
		{
			game->raycast.hit = 1;
			game->raycast.is_door = 1;
		}
	}
}

void	perp_wall_dist(t_game_data *game)
{
	if (game->raycast.side == 0)
		game->raycast.perpwalldist = (game->raycast.sidedistx - \
		game->raycast.deltadistx);
	else
		game->raycast.perpwalldist = (game->raycast.sidedisty - \
		game->raycast.deltadisty);
}
