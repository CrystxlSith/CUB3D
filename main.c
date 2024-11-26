#include "includes/cub3d.h"

void    ft_mlx_init(t_game_data *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        free(game->mlx);
        ft_printf("mlx_init fail");
    }
    game->win = mlx_new_window(game->mlx, 640, 440, "CUB3D");
    if (!game->win)
    {
        free(game->mlx);
        ft_printf("window launch fail");
    }
}


int handle_input(int keycode, t_game_data *game)
{
    if (keycode == XK_Escape)
        exit(0);
    if (keycode == XK_z)
        game->player.y -= 0.05;
    else if (keycode == XK_s)
        game->player.y += 0.05;
    else if (keycode == XK_q)
        game->player.x -= 0.05;
    else if (keycode == XK_d)
        game->player.x += 0.05;
    printf("%d\n", keycode);
    return (0);
}


int main(int argc, char const *argv[])
{
    t_game_data  game;

    ft_mlx_init(&game);
    game_data_init(&game);
    image_init(&game);
    draw_map(&game);
    mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);

    mlx_loop(game.mlx);
	// mlx_hook(game.win, 17, 0, end, data);
	// mlx_hook(game.win, 12, 32768, make_mouv, data);
    return 0;
}
