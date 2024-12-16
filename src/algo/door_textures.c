#include "../../includes/cub3d.h"

void	door_texture_calculation(t_game_data *game)
{
	if (game->door_nbr != 0)
	{
		if (game->raycast.side == 0)
			game->raycast.wallx = game->raycast.posy + \
				game->raycast.perpwalldist * game->raycast.raydiry;
		else
			game->raycast.wallx = game->raycast.posx + \
				game->raycast.perpwalldist * game->raycast.raydirx;
		game->raycast.wallx -= floor(game->raycast.wallx);
		game->raycast.texx = (int)(game->raycast.wallx * \
			(double)game->textures[4].width);
		if (game->raycast.side == 0 && game->raycast.raydirx > 0)
			game->raycast.texx = game->textures[4].width \
				- game->raycast.texx - 1;
		if (game->raycast.side == 1 && game->raycast.raydiry < 0)
			game->raycast.texx = game->textures[4].width \
				- game->raycast.texx - 1;
	}
}

void	verline_door(t_game_data *game, int x, int start, int end)
{
	int	color;

	if (game->door_nbr != 0)
	{
		while (start <= end)
		{
			game->raycast.texy = (((start * 2 - SCREEN_HEIGHT + \
				game->raycast.line_height) * \
				game->textures[4].height) / \
				game->raycast.line_height) / 2;
			if (game->raycast.texy < 0)
				game->raycast.texy = 0;
			if (game->raycast.texy >= game->textures[4].height)
				game->raycast.texy = game->textures[4].height - 1;
			color = *(int *)(game->textures[4].addr + \
				(game->raycast.texy * \
				game->textures[4].line_length \
				+ game->raycast.texx * \
				(game->textures[4].bpp / 8)));
			my_mlx_pixel_put(game, x, start, color);
			start++;
		}
	}
}
