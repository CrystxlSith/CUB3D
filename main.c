
// void    move_player(t_game_data *game, double speed)
// {
//     double  newposX;
//     double  newposY;

//     // printf("%d && %d\n", (int)game->player.x, (int)game->player.y);
//     newposX = speed * cos(game->player.angle);
//     newposY = speed * sin(game->player.angle);
// // if (game->map[(int)(game->player.y + newposY * 1.1)][(int)(game->player.x + newposX * 1.1)] == '1')
// //     return;

//     game->player.x += newposX;
//     game->player.y += newposY;
//     game->raycast.posX += newposX;
//     game->raycast.posY+= newposY;
// }
#include "includes/cub3d.h"

void    ft_mlx_init(t_game_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game->mlx);
		ft_printf("mlx_init fail");
	}
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, \
	SCREEN_HEIGHT, "raycaster");
	if (!game->win)
	{
		free(game->mlx);
		ft_printf("window launch fail");
	}
}

void	turn_left(t_game_data *game, double rotation_speed)
{
	double	old_dirX;
	double	old_planeX;

	old_dirX = game->raycast.dirX;
	game->raycast.dirX = game->raycast.dirX * cos(rotation_speed) - \
	game->raycast.dirY * sin(rotation_speed);
	game->raycast.dirY = old_dirX * sin(rotation_speed) + \
	game->raycast.dirY * cos(rotation_speed);
	old_planeX = game->raycast.planeX;
	game->raycast.planeX = game->raycast.planeX * cos(rotation_speed) - \
	game->raycast.planeY * sin(rotation_speed);
	game->raycast.planeY = old_planeX * sin(rotation_speed) + \
	game->raycast.planeY * cos(rotation_speed);
}

	// game->player.angle -= rotation_speed;
	// if (game->player.angle < 0) 
	//     game->player.angle += 2 * PI;
	// printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle
void    turn_right(t_game_data *game, double rotation_speed)
{
	double	old_dirX;
	double	old_planeX;

	old_dirX = game->raycast.dirX;
	game->raycast.dirX = game->raycast.dirX * cos(-rotation_speed) - \
	game->raycast.dirY * sin(-rotation_speed);
	game->raycast.dirY = old_dirX * sin(-rotation_speed) + \
	game->raycast.dirY * cos(-rotation_speed);
	old_planeX = game->raycast.planeX;
	game->raycast.planeX = game->raycast.planeX * cos(-rotation_speed) - \
	game->raycast.planeY * sin(-rotation_speed);
	game->raycast.planeY = old_planeX * sin(-rotation_speed) + \
	game->raycast.planeY * cos(-rotation_speed);
	// game->player.angle += rotation_speed;
	// if (game->player.angle < 0) 
	//     game->player.angle -= 2 * PI;
	// printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle

}

void    move_front(t_game_data *game, double moveSpeed)
{
	double newposX = game->player.x + game->raycast.dirX * moveSpeed;
	double newposY = game->player.y + game->raycast.dirY * moveSpeed;

	if (game->map[(int)newposX][(int)game->player.y] != '1')
	{
		game->player.x = newposX;
		game->raycast.posX = newposX;
	}
	if (game->map[(int)game->player.x][(int)newposY] != '1')
	{
		game->player.y = newposY;
		game->raycast.posY = newposY;
	}
}

void    move_back(t_game_data *game, double moveSpeed)
{
	double newposX = game->player.x - game->raycast.dirX * moveSpeed;
	double newposY = game->player.y - game->raycast.dirY * moveSpeed;

	if (game->map[(int)newposX][(int)game->player.y] != '1')
	{
		game->player.x = newposX;
		game->raycast.posX = newposX;
	}
	if (game->map[(int)game->player.x][(int)newposY] != '1')
	{
		game->player.y = newposY;
		game->raycast.posY = newposY;
	}
}

int handle_input(int keycode, t_game_data *game)
{
	if (keycode == XK_Escape)
		game->key.escape = 1;
	else if (keycode == 119)
		game->key.forward = 1;
	else if (keycode == 115)
		game->key.backward = 1;
	else if (keycode == 97)
		game->key.turn_left = 1;
	else if (keycode == 100)
		game->key.turn_right = 1;
	printf("Key pressed: %d\n", keycode);
	update_player(game);
	return (0);
}


int input_release(int keycode, t_game_data *game)
{
	if (keycode == 119)
		game->key.forward = 0;
	else if (keycode == 115)
		game->key.backward = 0;
	else if (keycode == 97)
		game->key.turn_left = 0;
	else if (keycode == 100)
		game->key.turn_right = 0;
	return (0);
}

int	close_game(t_game_data *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int main(int argc, char const *argv[])
{
	t_game_data  game;
	t_key		key;

	ft_mlx_init(&game);
	game_data_init(&game);
	image_init(&game);
	// draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, &handle_input, &game);
	mlx_hook(game.win, 33, 1L << 17, &close_game, &game);
	mlx_hook(game.win, 3, 1L << 1, &input_release, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_do_sync(game.mlx);
	mlx_loop(game.mlx);
	// mlx_hook(game.win, 17, 0, end, data);
	// mlx_hook(game.win, 12, 32768, make_mouv, data);
	return 0;
}
