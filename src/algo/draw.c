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

void	draw_circle(t_game_data *game, int center_x, int center_y, \
	int color)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			if ((x * x) + (y * y) <= (3 * 3))
				my_mlx_pixel_put(game, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_game_data *game, double x, double y)
{
	draw_circle(game, x, y, 0xFF0000);
}
