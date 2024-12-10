#include "includes/cub3d.h"

void	ft_mlx_init(t_game_data *game)
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

void	turn_right(t_game_data *game, double rotation_speed)
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

void	move_front(t_game_data *game, double moveSpeed)
{
	double	newposX;
	double	newposY;
	double	new_speed;

	new_speed = game->raycast.delta_time * moveSpeed * 60.0;
	newposX = game->player.x + game->raycast.dirX * new_speed;
	newposY = game->player.y + game->raycast.dirY * new_speed;
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

void	move_back(t_game_data *game, double moveSpeed)
{
	double	newposX;
	double	newposY;
	double	new_speed;

	new_speed = game->raycast.delta_time * moveSpeed * 60.0;
	newposX = game->player.x - game->raycast.dirX * new_speed;
	newposY = game->player.y - game->raycast.dirY * new_speed;
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

int	handle_input(int keycode, t_game_data *game)
{
	if (keycode == XK_Escape)
		game->key.escape = 1;
	else if (keycode == XK_w)
		game->key.forward = 1;
	else if (keycode == XK_s)
		game->key.backward = 1;
	else if (keycode == XK_a)
		game->key.turn_left = 1;
	else if (keycode == XK_d)
		game->key.turn_right = 1;
	return (0);
}

int	input_release(int keycode, t_game_data *game)
{
	if (keycode == XK_w)
		game->key.forward = 0;
	else if (keycode == XK_s)
		game->key.backward = 0;
	else if (keycode == XK_a)
		game->key.turn_left = 0;
	else if (keycode == XK_d)
		game->key.turn_right = 0;
	return (0);
}

int	close_game(t_game_data *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	handle_mouse_motion(int x, int y, t_game_data *game)
{
	static int	last_x; //Conserver la dernière position X de la souris
	int			delta_x;
	double		rotation_speed;
	double		old_dir_x;
	double		old_plane_x;

	(void)y;
	delta_x = x - last_x; // Calculer le déplacement horizontal
	last_x = x;
	rotation_speed = 0.003; // Ajuster la sensibilité
	old_dir_x = game->raycast.dirX;
	game->raycast.dirX = game->raycast.dirX * cos(-delta_x * rotation_speed) \
		- game->raycast.dirY * sin(-delta_x * rotation_speed);
	game->raycast.dirY = old_dir_x * sin(-delta_x * rotation_speed) \
		+ game->raycast.dirY * cos(-delta_x * rotation_speed);
	old_plane_x = game->raycast.planeX;
	game->raycast.planeX = game->raycast.planeX * cos(-delta_x * \
		rotation_speed) - game->raycast.planeY * sin(-delta_x * rotation_speed);
	game->raycast.planeY = old_plane_x * sin(-delta_x * rotation_speed) \
		+ game->raycast.planeY * cos(-delta_x * rotation_speed);
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
	mlx_hook(game.win, MotionNotify, PointerMotionMask, \
		handle_mouse_motion, &game);
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
