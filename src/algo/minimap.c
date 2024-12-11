#include "../../includes/cub3d.h"

void    minimap(t_game_data *data)
{
    int	x;
    int	y;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                draw_square(data, x * 16, y * 16, 16, 0x000000000);
            else if (data->map[y][x] == '0' || data->map[y][x] == 'N')
                draw_square(data, x * 16, y * 16, 16, 0x00FFFFFF);
            x++;
        }
        y++;
    }
    draw_player(data, data->player.y, data->player.x, 3, 0x00FF0000);
    draw_line(data, data->player.x * 16, data->player.y * 16, data->player.x * 16 + cos(data->player.angle) * 20, 0x00FF0000);
    draw_line(data, data->player.x * 16, data->player.y * 16, data->player.y * 16 + sin(data->player.angle) * 20, 0x00FF0000);
}
