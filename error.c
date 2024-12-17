#include "includes/cub3d.h"

void	free_all(t_game_data *game)
{
	if (game->map)
		free_everything(game->map);
	if (game->file)
		free_everything(game->file);
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
}

void	exit_error(t_game_data *game, char *error)
{
	int	i;

	ft_putstr_fd(error, 2);
	i = 0;
	while (i < 7)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	free_all(game);
	if (game->ray_img)
		mlx_destroy_image(game->mlx, game->ray_img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(EXIT_FAILURE);
}

void	exit_error_map(t_game_data *game, char *error)
{
	int	i;

	ft_putstr_fd(error, 2);
	i = 0;
	free_all(game);
	if (game->ray_img)
		mlx_destroy_image(game->mlx, game->ray_img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(EXIT_FAILURE);
}
