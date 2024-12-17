#include "includes/cub3d.h"


/*
	gerer les free dans les erreurs lors de l'initialisation
	verifier le .xpm avant de le charger

*/

/*
	erreur valgrind si porte sans murs autour
	==19685== Conditional jump or move depends on uninitialised value(s)
	==19685==    at 0x11128C: handle_door (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x111190: input_release (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x1154C5: mlx_loop (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x113BAC: main (in /home/rottbliss/42/cub/cub3d)
	==19685==
	==19685== Conditional jump or move depends on uninitialised value(s)
	==19685==    at 0x11129A: handle_door (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x111190: input_release (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x1154C5: mlx_loop (in /home/rottbliss/42/cub/cub3d)
	==19685==    by 0x113BAC: main (in /home/rottbliss/42/cub/cub3d)
*/
int	main(int argc, char *argv[])
{
	t_game_data	game;

	if (argc != 2)
		return (0);
	ft_mlx_init(&game);
	if (fill_map_struct(&game, argv) == -1)
		return (0);
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
