#include "includes/cub3d.h"

void    draw_raycast(t_game_data *game, int x)
{
    int line_height;
    int draw_start;
    int draw_end;

    line_height = (int)(SCREEN_WIDTH / game->raycast.perpWallDist); // Height of line
    draw_start = -line_height / 2 + SCREEN_WIDTH / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + SCREEN_WIDTH / 2;
    if (draw_end >= SCREEN_WIDTH)
        draw_end = SCREEN_WIDTH - 1;

}

void    digital_differential_analyzer(t_game_data *game, int x)
{
    while (game->raycast.hit == 0)
    {
        if (game->raycast.sideDistX < game->raycast.sideDistY)
        {
            game->raycast.sideDistX += game->raycast.deltaDistX;
            game->player.mapX += game->raycast.stepX;
            game->raycast.side = 0;
        }
        else
        {
            game->raycast.sideDistY += game->raycast.deltaDistY;
            game->player.mapY += game->raycast.stepY;
            game->raycast.side = 1;
        }
        if (game->map[game->player.mapX][game->player.mapY] > 0)
            game->raycast.hit = 1;
    }
    if (game->raycast.side == 0)
        game->raycast.perpWallDist = (game->raycast.sideDistX - game->raycast.sideDistY);
    else
        game->raycast.perpWallDist = (game->raycast.sideDistY - game->raycast.sideDistX);
    draw_raycast(game, x);
}
