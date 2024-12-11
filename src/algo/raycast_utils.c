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

	game->raycast.time = get_time_in_seconds();
	game->raycast.delta_time = game->raycast.time - game->raycast.oldtime;
	game->raycast.oldtime = game->raycast.time;
	fps = 1.0 / game->raycast.delta_time;
	str_fps = ft_strjoin("FPS: ", ft_itoa(fps));
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - 50, 10, 0xFFFFFF, str_fps);
	free(str_fps);
}
