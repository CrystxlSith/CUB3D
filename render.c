#include "includes/cub3d.h"

void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char	*dst;

    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT)
    {
	    dst = data->img_addr + (y * data->line_length + x * (data->bpp / 8));
	    *(unsigned int*)dst = color;
    }
}


void draw_square(t_game_data *game, int x, int y, int size, int color)
{
    int i, j;

    for (i = 0; i < size; i++) // Hauteur du carré
    {
        for (j = 0; j < size; j++) // Largeur du carré
            my_mlx_pixel_put(game, x + j, y + i, color); // Placer chaque pixel
    }
}

void    draw_map(t_game_data *game)
{
    int x;
    int y;

    y = 0;
    game->img = mlx_new_image(game->mlx, MAP_WIDTH * SCREEN_WIDTH, MAP_HEIGHT * SCREEN_HEIGHT);
    game->img_addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
    while (game->map[y])
    {
        x = 0;

        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
                draw_square(game, x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, 0x00FF0000);
            x++;
        }
        
        y++;
    }
}

void draw_circle(t_game_data *game, int center_x, int center_y, int radius, int color)
{
    int x, y;

    // Parcourir un carré englobant tout le cercle
    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            // Vérifier si le pixel (x, y) est dans le cercle
            if ((x * x) + (y * y) <= (radius * radius))
            {
                my_mlx_pixel_put(game, center_x + x, center_y + y, color); // Placer le pixel
            }
        }
    }
}

void draw_player(t_game_data *game, double x, double y, int radius, int color)
{
    int draw_x;
    int draw_y;

    // Calculer la position de dessin
    draw_x = x * CELL_SIZE + (CELL_SIZE / 2);
    draw_y = y * CELL_SIZE + (CELL_SIZE / 2);

    // Dessiner un cercle
    draw_circle(game, draw_x, draw_y, radius, color);
}

void update_player(t_game_data *game)
{
    int player_size = CELL_SIZE / 8;

    // Effacer l'ancienne position et remplacer avec du noir
    draw_player(game, game->player.old_x, game->player.old_y, player_size, 0x000000);

    // Dessiner la nouvelle position
    draw_player(game, game->player.x, game->player.y, player_size, 0xFFFFFF);

    // Mettre à jour les anciennes coordonnées
    game->player.old_x = game->player.x;
    game->player.old_y = game->player.y;
}

int    render_frame(t_game_data *game)
{
    // mlx_clear_window(game->mlx, game->win);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    update_player(game);
    // mlx_put_image_to_window(game->mlx, game->win, game->player_img, 0, 0);
    return (0);
}