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

	game->raycast.time = get_time_in_seconds();
	game->raycast.delta_time = game->raycast.time - game->raycast.oldtime;
	game->raycast.oldtime = game->raycast.time;
	fps = 1.0 / game->raycast.delta_time;
	printf("FPS: %.2f\n", fps);
}
