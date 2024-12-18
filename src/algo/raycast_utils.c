/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiliber <agiliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:32:01 by agiliber          #+#    #+#             */
/*   Updated: 2024/12/19 14:33:24 by agiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_time_in_seconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + (time.tv_usec / 1000000.0));
}

void	fps_count(t_game_data *game)
{
	double	fps;
	char	*str_fps;
	char	*fps_value;

	game->raycast.time = get_time_in_seconds();
	game->raycast.delta_time = game->raycast.time - game->raycast.oldtime;
	game->raycast.oldtime = game->raycast.time;
	fps = 1.0 / game->raycast.delta_time;
	fps_value = ft_itoa(fps);
	str_fps = ft_strjoin("FPS: ", fps_value);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - 50, 10, \
	0xFFFFFF, str_fps);
	game->movespeed = (game->raycast.delta_time * 5.0) / 3;
	game->rotspeed = (game->raycast.delta_time * 3.0) / 2;
	free(fps_value);
	free(str_fps);
}
