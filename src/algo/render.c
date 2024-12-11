#include "../../includes/cub3d.h"

void	draw_line(t_game_data *game, int x, int start, int end, int color)
{
	int	y;

	if (start < 0)
		start = 0;
	if (end >= SCREEN_HEIGHT)
		end = SCREEN_HEIGHT - 1;
	y = start;
	while (y <= end)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

void	update_player(t_game_data *game)
{
	if (game->key.escape)
		exit(0);
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
	game->ray_img = mlx_new_image(game->mlx, 1920, 1080);
	game->ray_addr = mlx_get_data_addr(game->ray_img, &game->bpp, \
		&game->line_length, &game->endian);
	mlx_clear_window(game->mlx, game->win);
	draw_floor_and_ceiling(game);
	update_player(game);
	raycasting(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->ray_img, 0, 0);
	fps_count(game);
	mlx_destroy_image(game->mlx, game->ray_img);
	return (0);
}
