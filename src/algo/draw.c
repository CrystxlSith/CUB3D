#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = data->ray_addr + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_game_data *game, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game_data *game)
{
	int	x;
	int	y;

	y = 0;
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_addr = mlx_get_data_addr(game->img, &game->bpp, \
	&game->line_length, &game->endian);
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(game, x * CELL_SIZE, y * CELL_SIZE, \
				CELL_SIZE, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	draw_circle(t_game_data *game, int center_x, int center_y, \
	int radius, int color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x) + (y * y) <= (radius * radius))
				my_mlx_pixel_put(game, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game_data *game, double x, double y, \
	int radius, int color)
{
	int	draw_x;
	int	draw_y;

	// Calculer la position de dessin
	draw_x = (x * CELL_SIZE) + (CELL_SIZE / 2);
	draw_y = (y * CELL_SIZE) + (CELL_SIZE / 2);
	// Dessiner un cercle
	draw_circle(game, draw_x, draw_y, radius, color);
}
