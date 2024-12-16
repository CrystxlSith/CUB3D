#include "includes/cub3d.h"

void    exit_error(t_game_data *game, char *error)
{
    int i;

    ft_putstr_fd(error, 2);
    free_everything(game->map);
    free_everything(game->file);
    i = 0;
    if (game->textures)
    {
        while (i < 5)
        {
            if (game->textures[i].img)
                mlx_destroy_image(game->mlx, game->textures[i].img);
            ft_printf("Texture %d\n", i);
            i++;
        }
    }
    free(game->floor_color);
    free(game->ceiling_color);
    free(game->north_texture);
    free(game->south_texture);
    free(game->west_texture);
    free(game->east_texture);
	mlx_destroy_image(game->mlx, game->ray_img);
    if (game->mlx && game->win)
    {
        mlx_destroy_window(game->mlx, game->win);
    }
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    exit(EXIT_FAILURE);
}
