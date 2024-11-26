#include "includes/cub3d.h"

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
        "1000000001",
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

    game->bpp = 32;
    game->endian = 0;
    game->line_length = 2560;

    printf("Player initialized at: x = %.1f, y = %.1f\n", game->player.x, game->player.y);
}