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

void    step_dist(t_game_data *game)
{
    if (game->raycast.rayDirX < 0)
    {
        game->raycast.stepX = -1;
        game->raycast.sideDistX = (game->raycast.posX + game->player.mapX) * game->raycast.deltaDistX;
    }
    else
    {
        game->raycast.stepX = 1;
        game->raycast.sideDistX = (game->player.mapX + 1.0 - game->raycast.posX) * game->raycast.deltaDistX;
    }
    if (game->raycast.rayDirY < 0)
    {
        game->raycast.stepY = -1;
        game->raycast.sideDistY = (game->raycast.posY + game->player.mapY) * game->raycast.deltaDistY;
    }
    else
    {
        game->raycast.stepY = 1;
        game->raycast.sideDistY = (game->player.mapY + 1.0 - game->raycast.posY) * game->raycast.deltaDistY;
    }  
}

void    raycalculate(t_game_data *game, int x)
{
    if (game->raycast.rayDirX == 0)
        game->raycast.deltaDistX = 1e30; // Avoid division per 0
    else
        game->raycast.deltaDistX = fabs(1 / game->raycast.rayDirX);
    if (game->raycast.rayDirY == 0)
        game->raycast.deltaDistY = 1e30;
    else
        game->raycast.deltaDistY = fabs(1 / game->raycast.rayDirY);
    game->raycast.hit = 0;
    step_dist(game);
    digital_differential_analyzer(game, x);
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
        raycalculate(game, i);
        i++;
    }
}
