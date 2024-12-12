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
    int x, y;
    double map_offset_x, map_offset_y;

    // Define the minimap size and offsets to center the player
    double minimap_size = 10.0; // Half the width/height of the minimap in tiles
    double tile_size = 16.0;    // Size of each tile in pixels

    // Calculate the map section to display around the player
    map_offset_x = data->player.y - minimap_size / 2.0;
    map_offset_y = data->player.x - minimap_size / 2.0;

    // Debugging output for offsets

    // Draw the minimap tiles
    for (y = 0; y < (int)minimap_size; y++)
    {
        for (x = 0; x < (int)minimap_size; x++)
        {
            // Calculate the world position corresponding to the minimap tile
            double map_x = map_offset_x + x;
            double map_y = map_offset_y + y;

            // Check if the map position is within bounds
            if ((int)map_y >= 0 && (int)map_y < data->map_height && (int)map_x >= 0 && (int)map_x < data->map_width)
            {
                if (data->map[(int)map_y][(int)map_x] == '1')
                    draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000); // Wall
                else if (data->map[(int)map_y][(int)map_x] == '0' || data->map[(int)map_y][(int)map_x] == 'N')
                    draw_square(data, x * tile_size, y * tile_size, tile_size, 0xFFFFFF); // Walkable tile
            }
            else
            {
                // Draw a black square if out of bounds
                draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000);
            }
        }
    }

    // Correct the player's position in the minimap
    double player_minimap_x = (data->player.x - map_offset_x) * tile_size;
    double player_minimap_y = (data->player.y - map_offset_y) * tile_size;

    // Debugging output for player position

    // Draw the player at its exact position on the minimap
    draw_player(data, player_minimap_x, player_minimap_y, 3, 0xFF0000);

    // // Optionally draw a direction line from the player
    // double line_end_x = player_minimap_x + cos(data->player.angle) * tile_size;
    // double line_end_y = player_minimap_y + sin(data->player.angle) * tile_size;
    // draw_line(data, player_minimap_x, player_minimap_y, line_end_x, line_end_y, 0xFF0000);
}


// void minimap(t_game_data *data)
// {
//     int x;
//     int y;
//     double map_offset_x;
//     double map_offset_y;
//     int minimap_size = 8;
//     int tile_size = 16;

//     map_offset_y = data->player.x - (double)minimap_size / 2;
//     map_offset_x = data->player.y - (double)minimap_size / 2;
//     y = 0;
//     while (y < minimap_size)
//     {
//         x = 0;
//         while (x < minimap_size)
//         {
//             int map_x = map_offset_x + x;
//             int map_y = map_offset_y + y;
//             if (map_y >= 0 && map_y < data->map_height && map_x >= 0 && map_x < data->map_width)
//             {
//                 if (data->map[map_y][map_x] == '1')
//                     draw_square(data, x * tile_size, y * tile_size, tile_size, 0x000000);
//                 else if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
//                     draw_square(data, x * tile_size, y * tile_size, tile_size, 0xFFFFFF);
//                 else
//                     draw_square(data, x * tile_size, y * tile_size, tile_size, 0x8B00FF); // Draw in purple if not wall, player, or floor
//             }
//             else
//                 draw_square(data, x * tile_size, y * tile_size, tile_size, 0x8B00FF); // Draw in dark violet if out of bounds
//             x++;
//         }
//         y++;
//     }
//     draw_player(data, ((minimap_size / 2) * tile_size) + 6, ((minimap_size / 2) * tile_size) + 6, 3, 0xFF0000);
// }


