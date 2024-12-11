#include "../../includes/cub3d.h"

#include "../../includes/cub3d.h"

void    minimap(t_game_data *data)
{
    int x;
    int y;
    int map_x;
    int map_y;
    int offset_x = data->player.x * 16 - (SCREEN_WIDTH / 2);
    int offset_y = data->player.y * 16 - (SCREEN_HEIGHT / 2);

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            map_x = x * 16 - offset_x;
            map_y = y * 16 - offset_y;
            if (data->map[y][x] == '1')
                draw_square(data, map_x, map_y, 16, 0x00000000);
            else if (data->map[y][x] == '0' || data->map[y][x] == 'N')
                draw_square(data, map_x, map_y, 16, 0x00FFFFFF);
            x++;
        }
        y++;
    }
    draw_player(data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, 0x00FF0000);
    draw_line(data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2 + cos(data->player.angle) * 20, 0x00FF0000);
    draw_line(data, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2 + sin(data->player.angle) * 20, 0x00FF0000);
}

// void    minimap(t_game_data *data)
// {
//     int	x;
//     int	y;

//     y = 0;
//     while (data->map[y])
//     {
//         x = 0;
//         while (data->map[y][x])
//         {
//             if (data->map[y][x] == '1')
//                 draw_square(data, x * 16, y * 16, 16, 0x000000000);
//             else if (data->map[y][x] == '0' || data->map[y][x] == 'N')
//                 draw_square(data, x * 16, y * 16, 16, 0x00FFFFFF);
//             x++;
//         }
//         y++;
//     }
//     draw_player(data, data->player.y, data->player.x, 3, 0x00FF0000);
//     draw_line(data, data->player.x * 16, data->player.y * 16, data->player.x * 16 + cos(data->player.angle) * 20, 0x00FF0000);
//     draw_line(data, data->player.x * 16, data->player.y * 16, data->player.y * 16 + sin(data->player.angle) * 20, 0x00FF0000);
// }
