#include "includes/cub3d.h"

void draw_line(t_game_data *game, int x, int start, int end, int color)
{
    int y;

    // Vérifie que les coordonnées sont dans les limites de l'écran
    if (start < 0)
        start = 0;
    if (end >= SCREEN_HEIGHT)
        end = SCREEN_HEIGHT - 1;

    // Dessine une ligne verticale, pixel par pixel
    y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(game, x, y, color); // Placer un pixel à la position (x, y)
        y++;
    }
}


void    raycasting(t_game_data *game)
{
    int     i;
    double  cameraX;

    cameraX = 0;
    i = 0;
    while (i < SCREEN_WIDTH)
    {
        cameraX = 2 * i / (double)SCREEN_WIDTH - 1;
        game->raycast.rayDirX = game->raycast.dirX + game->raycast.planeX * cameraX;
        game->raycast.rayDirY = game->raycast.dirY + game->raycast.planeY * cameraX;
        game->player.mapX = (int)game->player.x;
        game->player.mapY = (int)game->player.y;
        i++;
    }
}
