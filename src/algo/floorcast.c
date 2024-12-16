#include "../../includes/cub3d.h"

static void	init_floorcast_y(t_game_data *game, int y, int *p)
{
	game->raycast.raydirx0 = game->raycast.dirx - game->raycast.planex;
	game->raycast.raydiry0 = game->raycast.diry - game->raycast.planey;
	game->raycast.raydirx1 = game->raycast.dirx + game->raycast.planex;
	game->raycast.raydiry1 = game->raycast.diry + game->raycast.planey;
	*p = y - SCREEN_HEIGHT / 2;
	game->raycast.posz = 0.5 * SCREEN_HEIGHT;
	game->raycast.rowdistance = game->raycast.posz / *p;
	game->raycast.floorstepx = game->raycast.rowdistance * \
		(game->raycast.raydirx1 - game->raycast.raydirx0) / SCREEN_WIDTH;
	game->raycast.floorstepy = game->raycast.rowdistance * \
		(game->raycast.raydiry1 - game->raycast.raydiry0) / SCREEN_WIDTH;
	game->raycast.floorx = game->player.x + game->raycast.rowdistance * \
		game->raycast.raydirx0;
	game->raycast.floory = game->player.y + game->raycast.rowdistance * \
		game->raycast.raydiry0;
}

static void	init_floorcast_x(t_game_data *game)
{
	game->raycast.cellx = (int)(game->raycast.floorx);
	game->raycast.celly = (int)(game->raycast.floory);
	game->raycast.tx = (int)(game->textures[4].width * \
		(game->raycast.floorx - game->raycast.cellx)) & \
		(game->textures[4].width - 1);
	game->raycast.ty = (int)(game->textures[4].height * \
		(game->raycast.floory - game->raycast.celly)) & \
		(game->textures[4].height - 1);
	game->raycast.floorx += game->raycast.floorstepx;
	game->raycast.floory += game->raycast.floorstepy;

}

void	floorcasting(t_game_data *game)
{
    int	y;
    int	x;
    int	p;
    
    y = 0;
    while (y < SCREEN_HEIGHT)
    {
        init_floorcast_y(game, y, &p);
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            init_floorcast_x(game);
            my_mlx_pixel_put(game, x, y, \
                *(int *)(game->textures[2].addr + \
                (game->raycast.ty * game->textures[2].line_length + \
                game->raycast.tx * (game->textures[2].bpp / 8))));
            my_mlx_pixel_put(game, x, SCREEN_HEIGHT - y - 1, \
                *(int *)(game->textures[3].addr + \
                (game->raycast.ty * game->textures[3].line_length + \
                game->raycast.tx * (game->textures[3].bpp / 8))));
            
            x++;
        }
        y++;
    }
}