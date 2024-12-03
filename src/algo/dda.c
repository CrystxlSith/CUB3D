#include "../../includes/cub3d.h"

static void	decide_wall_color(t_game_data *game, int *color)
{
	if (game->raycast.side == 0)
	{
		if (game->raycast.stepX > 0)
			*color = rgbBLUE;
		else
			*color = rgbDEFAULT;
	}
	else
	{
		if (game->raycast.stepY > 0)
			*color = rgbRED;
		else
			*color = rgbGREEN;
	}
	if (game->raycast.side == 1)
		*color = *color / 2;
}

static void	verLine(t_game_data *game, int x, int start, int end)
{
	int	color;

	decide_wall_color(game, &color);
	// printf("color = %d\n");
	// printf("%d\n", x);
	while (start <= end)
	{
		my_mlx_pixel_put(game, x, start, color);
		start++;
	}

}


static void	draw_raycast(t_game_data *game, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	// /int	color;

	line_height = (int)(SCREEN_WIDTH / game->raycast.perpWallDist); // Height of line
	draw_start = -line_height / 2 + SCREEN_WIDTH / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_WIDTH / 2;
	if (draw_end >= SCREEN_WIDTH)
		draw_end = SCREEN_WIDTH - 1;
	verLine(game, x, draw_start, draw_end);
	// fps_count(game);
}

void	digital_differential_analyzer(t_game_data *game, int x)
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
		// printf("Ray direction: rayDirX = %f, rayDirY = %f\n", game->raycast.rayDirX, game->raycast.rayDirY);
		// printf("Player position: mapX = %d, mapY = %d\n", game->player.mapX, game->player.mapY);

	}
	if (game->raycast.side == 0)
		game->raycast.perpWallDist = (game->raycast.sideDistX - game->raycast.deltaDistX);
	else
		game->raycast.perpWallDist = (game->raycast.sideDistY - game->raycast.deltaDistY);
	draw_raycast(game, x);
}
