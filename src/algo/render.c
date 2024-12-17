#include "../../includes/cub3d.h"

void	update_player(t_game_data *game)
{
	if (game->key.escape)
		exit_error(game, "Exit game\n");
	else if (game->key.forward)
		move_front(game, 0.1);
	else if (game->key.backward)
		move_back(game, 0.1);
	else if (game->key.turn_left)
		turn_left(game, 0.1);
	else if (game->key.turn_right)
		turn_right(game, 0.1);
}

int	render_frame(t_game_data *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_floor_and_ceiling(game);
	update_player(game);
	floorcasting(game);
	raycasting(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img, 0, 0);
	fps_count(game);
	return (0);
}
