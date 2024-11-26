#include "includes/cub3d.h"

void    image_init(t_game_data *game)
{
    // game->img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
    // game->img_addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);

    game->player_img = mlx_new_image(game->mlx, CELL_SIZE, CELL_SIZE);
    game->player_addr = mlx_get_data_addr(game->player_img, &game->bpp, &game->line_length, &game->endian);
}

void    game_data_init(t_game_data *game)
{
    int     i;
    int     j;

    i = 0;
    static char    *map[] = {
        "1111111111",
        "1000100101",
        "1000000101",
        "1000100101",
        "10000P0101",
        "1010001101",
        "1111111111",
        NULL

    };
    game->map = map;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'P')
            {
                game->player.y = i + 0.5;
                game->player.x = j + 0.5;
            }
            // else if (game->map[i][j] == '1')
            // {
            //     draw_wall(game, j, i, 0xCC0000);
            // }
            j++;
        }
        i++;
    }
    game->player.old_x = 0;
    game->player.old_y = 0;
    // game->bpp = 64;
    // game->endian = 0;
    // game->line_length = 2560;
    // ft_printf("bpp = %d\n", game->bpp);

    printf("Player initialized at: x = %.1f, y = %.1f\n", game->player.x, game->player.y);
}