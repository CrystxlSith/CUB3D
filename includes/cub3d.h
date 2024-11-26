#ifndef CUB3D_H
# define CUB3D_H


#define CELL_SIZE 64
#define MAP_HEIGHT 1920
#define MAP_WIDTH 1080

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


typedef struct s_player
{
    double  x;
    double  y;
} t_player;


typedef struct s_game_data
{
    char        **map;
    void        *mlx;
    void        *win;
    void        *img;
    char         *img_addr;
    int         bpp; // bits par pixel
    int         endian;
    int         line_length;
    t_player    player;
} t_game_data;

void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
void    game_data_init(t_game_data *game);
int    render_frame(t_game_data *game);
void    draw_player(t_game_data *game);

#endif