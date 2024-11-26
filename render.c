#include "includes/cub3d.h"

void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}


void draw_square(t_game_data *game, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++) // Hauteur du carré
    {
        for (j = 0; j < size; j++) // Largeur du carré
        {
            my_mlx_pixel_put(game, x + j, y + i, color); // Placer chaque pixel
        }
    }
}

void    draw_map(t_game_data *game)
{
    int x;
    int y;

    y = 0;
    game->img = mlx_new_image(game->mlx, MAP_WIDTH, MAP_HEIGHT);
    ft_printf("%d\n", game->bpp);
    game->img_addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
    while (game->map[y])
    {
        x = 0;

        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
            {
                draw_square(game, x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, 0x00FF0000);
            }
            x++;
        }
        
        y++;
    }    
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

}



void    draw_player(t_game_data *game)
{
    int     color;
    int     pixel_x;
    int     pixel_y;

    color = 0xFFFFFF; // blanc
    pixel_x = game->player.x * 64;
    pixel_y = game->player.y * 64;
    mlx_pixel_put(game->mlx, game->win, pixel_x, pixel_y, color);
}


int    render_frame(t_game_data *game)
{

    // mlx_clear_window(game->mlx, game->win);
    // draw_player(game);
    draw_map(game);

    return (0);
}