#include "../../includes/cub3d.h"

// static void	decide_wall_color(t_game_data *game, int *color)
// {
// 	if (game->raycast.side == 0)
// 	{
// 		if (game->raycast.stepX > 0)
// 			*color = rgbBLUE;
// 		else
// 			*color = rgbDEFAULT;
// 	}
// 	else
// 	{
// 		if (game->raycast.stepY > 0)
// 			*color = rgbRED;
// 		else
// 			*color = rgbGREEN;
// 	}
// 	if (game->raycast.side == 1)
// 		*color = *color / 2;
// }

static void	verLine(t_game_data *game, int x, int start, int end)
{
	int	color;

	while (start <= end)
	{
        game->raycast.texY = (((start * 2 - SCREEN_HEIGHT + game->raycast.line_height) * game->textures[game->raycast.texNum].height) / game->raycast.line_height) / 2;
        color = *(int*)(game->textures[game->raycast.texNum].addr + (game->raycast.texY * game->textures[game->raycast.texNum].line_length + game->raycast.texX * (game->textures[game->raycast.texNum].bpp / 8)));
		my_mlx_pixel_put(game, x, start, color);
		start++;
	}
	
}


void	draw_raycast(t_game_data *game, int x)
{
	int	draw_start;
	int	draw_end;

	game->raycast.line_height = (int)(SCREEN_HEIGHT / game->raycast.perpWallDist); // Height of line
	draw_start = -game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = game->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	verLine(game, x, draw_start, draw_end);
	// fps_count(game);
}

void	digital_differential_analyzer(t_game_data *game, int x)
{
	(void)x;
	game->raycast.hit = 0;
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
		if (game->map[game->player.mapX][game->player.mapY] == '1')
			game->raycast.hit = 1;
	}
	if (game->raycast.side == 0)
		game->raycast.perpWallDist = (game->raycast.sideDistX - game->raycast.deltaDistX);
	else
		game->raycast.perpWallDist = (game->raycast.sideDistY - game->raycast.deltaDistY);
}
