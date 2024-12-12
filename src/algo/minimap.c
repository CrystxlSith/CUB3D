#include "../../includes/cub3d.h"

void    draw_line_minimap(t_game_data *data, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, color); // Function to draw a pixel at (x0, y0)

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void minimap(t_game_data *data)
{
    int x;
    int y;
    int map_offset_x;
    int map_offset_y;
    int minimap_size = 8; // Half the width/height of the minimap in tiles
    int tile_size = 16;   // Size of each tile in pixels

    map_offset_y = data->player.x - minimap_size / 2;
    map_offset_x = data->player.y - minimap_size / 2;
    y = 0;
    while (y < minimap_size)
    {
        x = 0;
        while (x < minimap_size)
        {
            int map_x = map_offset_x + x;
            int map_y = map_offset_y + y;
            if (map_y >= 0 && map_y < data->map_height && map_x >= 0 && map_x < data->map_width)
            {
                if (data->map[map_y][map_x] == '1')
                    draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000);
                else if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
                    draw_square(data, x * tile_size, y * tile_size, tile_size, 0xFFFFFF);
                else
                    draw_square(data, x * tile_size, y * tile_size, tile_size, 0x8B00FF); // Draw in purple if not wall, player, or floor
            }
            else
                draw_square(data, x * tile_size, y * tile_size, tile_size, 0x8B00FF); // Draw in dark violet if out of bounds
            x++;
        }
        y++;
    }
    draw_player(data, (minimap_size / 2) * tile_size, (minimap_size / 2) * tile_size, 3, 0xFF0000);
}


// void    minimap(t_game_data *data)
// {
//     int x;
//     int y;
//     int map_offset_x;
//     int map_offset_y;

//     // Define the minimap size and offsets to center the player
//     int minimap_size = 10; // Half the width/height of the minimap in tiles
//     int tile_size = 16; // Size of each tile in pixels

//     // Calculate the map section to display around the player
//     map_offset_x = data->player.x - minimap_size / 2 * tile_size;
//     map_offset_y = data->player.y - minimap_size / 2 * tile_size;

//     // Draw the minimap tiles
//     for (y = 0; y < minimap_size; y++)
//     {
//         for (x = 0; x < minimap_size; x++)
//         {
//             int map_x = map_offset_x + x * tile_size;
//             int map_y = map_offset_y + y * tile_size;

//             // Check if the map position is within bounds
//             if (map_y >= 0 && map_y < 10 && map_x >= 0 && map_x < 10)
//             {
//                 if (data->map[map_y][map_x] == '1')
//                     draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000);
//                 else if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
//                     draw_square(data, x * tile_size, y * tile_size, tile_size, 0xFFFFFF);
//             }
//             else
//             {
//                 // Draw a black square if out of bounds
//                 draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000);
//             }
//         }
//     }

//     // Draw the player at the center of the minimap
//     draw_player(data, (minimap_size / 2) * tile_size, (minimap_size / 2) * tile_size, 3, 0xFF0000);

//     // Optionally draw a direction line from the player
//     // int line_end_x = (minimap_size / 2) * tile_size + cos(data->player.angle) * tile_size * 2;
//     // int line_end_y = (minimap_size / 2) * tile_size + sin(data->player.angle) * tile_size * 2;
//     // draw_line_minimap(data, (minimap_size / 2) * tile_size, (minimap_size / 2) * tile_size, line_end_x, line_end_y, 0xFF0000);
// }


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
