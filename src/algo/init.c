#include "../../includes/cub3d.h"

void	image_init(t_game_data *game)
{
	game->ray_img = mlx_new_image(game->mlx, 1920, 1080);
	game->ray_addr = mlx_get_data_addr(game->ray_img, &game->bpp, &game->line_length, &game->endian);

    game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->north_texture, &game->textures[0].width, &game->textures[0].height);
    game->textures[0].addr = mlx_get_data_addr(game->textures[0].img, &game->textures[0].bpp, &game->textures[0].line_length, &game->textures[0].endian);
	

    game->textures[1].img = mlx_xpm_file_to_image(game->mlx, game->south_texture, &game->textures[1].width, &game->textures[1].height);
    game->textures[1].addr = mlx_get_data_addr(game->textures[1].img, &game->textures[1].bpp, &game->textures[1].line_length, &game->textures[1].endian);

    game->textures[2].img = mlx_xpm_file_to_image(game->mlx, game->west_texture, &game->textures[2].width, &game->textures[2].height);
    game->textures[2].addr = mlx_get_data_addr(game->textures[2].img, &game->textures[2].bpp, &game->textures[2].line_length, &game->textures[2].endian);

    game->textures[3].img = mlx_xpm_file_to_image(game->mlx, game->east_texture, &game->textures[3].width, &game->textures[3].height);
    game->textures[3].addr = mlx_get_data_addr(game->textures[3].img, &game->textures[3].bpp, &game->textures[3].line_length, &game->textures[3].endian);
	// game->ray_img = mlx_new_image(game->mlx, CELL_SIZE, CELL_SIZE);
	// game->ray_addr = mlx_get_data_addr(game->ray_img, &game->bpp, &game->line_length, &game->endian);

	// game->player_img = mlx_new_image(game->mlx, CELL_SIZE, CELL_SIZE);
	// game->player_addr = mlx_get_data_addr(game->player_img, &game->bpp, &game->line_length, &game->endian);
}

void	init_game(t_game_data *game)
{
	game->player.old_x = 0; // Player previous position
	game->player.old_y = 0;
	game->raycast.dirX = -1.0; // Initial vector direction
	game->raycast.dirY = 0.0;
	game->raycast.planeX = 0; // 2D raycaster of camera plane
	game->raycast.planeY = 0.66;
	game->raycast.deltaDistX = 0;
	game->raycast.deltaDistY = 0;
	game->raycast.sideDistX = 0;
	game->raycast.sideDistY = 0;
	game->raycast.perpWallDist = 0;
	game->raycast.hit = 0;
	game->raycast.stepX = 0;
	game->raycast.stepY = 0;
	game->raycast.side = 0;
	game->raycast.time = 0;
	game->raycast.oldTime = 0;
	game->raycast.rayDirX = 0;
	game->raycast.rayDirY = 0;
	game->key.forward = 0;
	game->key.backward = 0;
	game->key.turn_left = 0;
	game->key.turn_right = 0;
	game->key.escape = 0;
	printf("dirX: %.2f, dirY: %.2f\n", game->raycast.dirX, game->raycast.dirY);
}
