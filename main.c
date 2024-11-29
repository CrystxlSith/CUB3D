#include "includes/cub3d.h"

void    ft_mlx_init(t_game_data *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        free(game->mlx);
        ft_printf("mlx_init fail");
    }
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "raycaster");
    if (!game->win)
    {
        free(game->mlx);
        ft_printf("window launch fail");
    }
}

void    turn_left(t_game_data *game, double rotation_speed)
{
    game->player.angle -= rotation_speed;
    if (game->player.angle < 0) 
        game->player.angle += 2 * PI;
    printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle
}

void    turn_right(t_game_data *game, double rotation_speed)
{
    game->player.angle += rotation_speed;
    if (game->player.angle < 0) 
        game->player.angle -= 2 * PI;
    printf("Player angle: %.2f\n", game->player.angle);  // Afficher l'angle

}

void    move_player(t_game_data *game, double speed)
{
    double  newposX;
    double  newposY;

    newposX = speed * cos(game->player.angle);
    newposY = speed * sin(game->player.angle);
    game->player.x += newposX;
    game->player.y += newposY;
    game->raycast.posX += newposX;
    game->raycast.posY+= newposY;
}

int handle_input(int keycode, t_game_data *game)
{
    if (keycode == XK_Escape)
        exit(0);
    if (keycode == XK_z)
        move_player(game, 0.05);
    else if (keycode == XK_s)
        move_player(game, -0.05);
    else if (keycode == XK_q)
        turn_left(game, 0.1);
    else if (keycode == XK_d)
        turn_right(game, 0.1);
    printf("%d\n", keycode);
    return (0);
}


int main(int argc, char const *argv[])
{
    t_game_data  game;

    ft_mlx_init(&game);
    game_data_init(&game);
    image_init(&game);
    draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_input, &game);
    mlx_loop_hook(game.mlx, render_frame, &game);

    mlx_loop(game.mlx);
	// mlx_hook(game.win, 17, 0, end, data);
	// mlx_hook(game.win, 12, 32768, make_mouv, data);
    return 0;
}
