#ifndef CUB3D_H
# define CUB3D_H


#define CELL_SIZE 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_HEIGHT 10
#define MAP_WIDTH 10
#define PI 3.14159265359

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>


typedef struct s_player
{
    double  x;
    double  y;
    double  old_x;
    double  old_y;
    double     angle;
} t_player;


typedef struct s_game_data
{
    int         bpp;
    char        **map;
    void        *mlx;
    void        *win;
    void        *img;
    void        *player_img;
    char         *img_addr;
    char        *player_addr;
    int         endian;
    int         line_length;
    t_player    player;
} t_game_data;


void    image_init(t_game_data *game);
void    draw_map(t_game_data *game);
void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
void    game_data_init(t_game_data *game);
int    render_frame(t_game_data *game);
void    draw_player(t_game_data *game, double x, double y, int radius, int color);

#endif