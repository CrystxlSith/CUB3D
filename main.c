#include "includes/cub3d.h"

void	ft_mlx_init(t_game_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game->mlx);
		ft_printf("mlx_init fail");
	}
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "raycaster");
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

	game->raycast.dirX = game->raycast.dirX * cos(rotation_speed) - game->raycast.dirY * sin(rotation_speed);
	game->raycast.dirY = old_dirX * sin(rotation_speed) + game->raycast.dirY * cos(rotation_speed);

	old_planeX = game->raycast.planeX;

	game->raycast.planeX = game->raycast.planeX * cos(rotation_speed) - game->raycast.planeY * sin(rotation_speed);
	game->raycast.planeY = old_planeX * sin(rotation_speed) + game->raycast.planeY * cos(rotation_speed);
	// game->player.angle -= rotation_speed;
	// if (game->player.angle < 0)
	//     game->player.angle += 2 * PI;
	// printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle
}

void	turn_right(t_game_data *game, double rotation_speed)
{
	double	old_dirX;
	double	old_planeX;

	old_dirX = game->raycast.dirX;

	game->raycast.dirX = game->raycast.dirX * cos(-rotation_speed) - game->raycast.dirY * sin(-rotation_speed);
	game->raycast.dirY = old_dirX * sin(-rotation_speed) + game->raycast.dirY * cos(-rotation_speed);

	old_planeX = game->raycast.planeX;

	game->raycast.planeX = game->raycast.planeX * cos(-rotation_speed) - game->raycast.planeY * sin(-rotation_speed);
	game->raycast.planeY = old_planeX * sin(-rotation_speed) + game->raycast.planeY * cos(-rotation_speed);

	// game->player.angle += rotation_speed;
	// if (game->player.angle < 0)
	//     game->player.angle -= 2 * PI;
	// printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle

}

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

void	move_front(t_game_data *game, double moveSpeed)
{
	if (game->map[(int)game->player.x + (int)game->raycast.dirX * (int)moveSpeed][(int)game->player.y] == false)
		game->player.x += game->raycast.dirX * moveSpeed;
	if (game->map[(int)game->player.x][(int)game->player.y + (int)game->raycast.dirY * (int)moveSpeed] == false)
		game->player.y += game->raycast.dirY * moveSpeed;
}

void	move_back(t_game_data *game, double moveSpeed)
{
	if (game->map[(int)game->player.x + (int)game->raycast.dirX * (int)moveSpeed][(int)game->player.y] == false)
		game->player.x -= game->raycast.dirX * moveSpeed;
	if (game->map[(int)game->player.x][(int)game->player.y + (int)game->raycast.dirY * (int)moveSpeed] == false)
		game->player.y -= game->raycast.dirY * moveSpeed;
}

int	handle_input(int keycode, t_game_data *game)
{
	if (keycode == XK_Escape)
		exit(0);
	if (keycode == XK_z)
		move_front(game, 0.1);// move_player(game, 0.05);
	else if (keycode == XK_s)
		move_back(game, 0.1); // move_player(game, -0.05);
	else if (keycode == XK_q)
		turn_left(game, 0.1);
	else if (keycode == XK_d)
		turn_right(game, 0.1);
	printf("%d\n", keycode);
	return (0);
}


int	main(int argc, char *argv[])
{
	t_game_data	game;

	if (argc != 2)
		return (0);
	ft_mlx_init(&game);
	if (fill_map_struct(&game, argv) == -1)
		return (0);
	image_init(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);

	mlx_loop(game.mlx);
	// mlx_hook(game.win, 17, 0, end, data);
	// mlx_hook(game.win, 12, 32768, make_mouv, data);
	return 0;
}
