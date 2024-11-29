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

typedef struct s_ray
{
    double  posX;
    double  posY;
    double  rayDirX;
    double  rayDirY;
    double  planeX;
    double  planeY;
    double  deltaDistX; // Distance to go through 1 case
    double  deltaDistY;
    double  sideDistx;
    double  sideDistY;
    double  perpWallDist;
    int     dirX;
    int     dirY;
    int     stepX; // Step direction (-1 or 1)
    int     stepY;
    int     hit; // Hit a wall
    int     side; // Where the wall is hit
    int     FOV; // Field of view
} t_ray;

typedef struct s_player
{
    double  x; // Player EXACT position
    double  y;
    int     mapX; // Player position (1 or 0)
    int     mapY;
    double  old_x; // Player previous exact position
    double  old_y;
    double  angle; // Player angle
} t_player;


typedef struct s_game_data
{
    int         bpp; // Bits per pixel
    double      time; // Time of current frame
    double      oldTime; // Time if previous frame
    char        **map;
    void        *mlx;
    void        *win;
    void        *img;
    void        *player_img;
    char        *ray_img;
    char        *ray_addr;
    char         *img_addr;
    char        *player_addr;
    int         endian;
    int         line_length;
    t_ray       raycast;
    t_player    player;
} t_game_data;


void    image_init(t_game_data *game);
void    draw_map(t_game_data *game);
void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
void    game_data_init(t_game_data *game);
int    render_frame(t_game_data *game);
void    draw_player(t_game_data *game, double x, double y, int radius, int color);
void    raycasting(t_game_data *game);

#endif