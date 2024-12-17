#include "../../includes/cub3d.h"

int	create_trgb(char *color)
{
	int	r;
	int	g;
	int	b;
	int	trgb;

	r = ft_atoi(color);
	while (*color && *color != ',')
		color++;
	if (*color == ',')
		color++;
	g = ft_atoi(color);
	while (*color && *color != ',')
		color++;
	if (*color == ',')
		color++;
	b = ft_atoi(color);
	trgb = (r * 65536 + g * 256 + b);
	return (trgb);
}

void	draw_floor_and_ceiling(t_game_data *game)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = create_trgb(game->floor_color);
	ceiling_color = create_trgb(game->ceiling_color);
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game, x, y, ceiling_color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (++x < SCREEN_WIDTH)
			my_mlx_pixel_put(game, x, y, floor_color);
		y++;
	}
}

void	image_verify(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!game->textures[i].img)
			exit_error(game, "texture fail");
		i++;
	}
	image_init2(game);
}

void	addr_verify(t_game_data *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!game->textures[i].addr)
			exit_error(game, "texture addr fail");
		i++;
	}
}
