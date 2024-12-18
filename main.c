#include "includes/cub3d.h"

/*
	gerer les free dans les erreurs lors de l'initialisation
	verifier le .xpm avant de le charger

*/
int	main(int argc, char *argv[])
{
	t_game_data	game;

	if (argc != 2)
		return (0);
	ft_mlx_init(&game);
	if (fill_map_struct(&game, argv) == -1)
		return (exit_error_map(&game, "Map error\n"), 0);
	if (texture_verify(&game) == -1)
		return (exit_error_map(&game, "Texture error\n"), 0);
	image_init(&game);
	init_doors(&game);
	mlx_hook(game.win, MotionNotify, PointerMotionMask, \
		handle_mouse_motion, &game);
	mlx_hook(game.win, 2, 1L << 0, &handle_input, &game);
	mlx_hook(game.win, 33, 1L << 17, &close_game, &game);
	mlx_hook(game.win, 3, 1L << 1, &input_release, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_do_sync(game.mlx);
	mlx_loop(game.mlx);
	return (0);
}
