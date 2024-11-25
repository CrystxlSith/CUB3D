#include "includes/cub3d.h"

void    ft_mlx_init(t_game_data *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        free(game->mlx);
        ft_printf("mlx_init fail");
    }
    game->win = mlx_new_window(game->mlx, 1920, 1080, "CUB3D");
    if (!game->win)
    {
        free(game->mlx);
        ft_printf("window launch fail");
    }
}

int main(int argc, char const *argv[])
{
    t_game_data  game;

    ft_mlx_init(&game);
    mlx_loop(game.mlx);
    return 0;
}
