#ifndef CUB3D_H
# define CUB3D_H

# define TRUE 1
# define FALSE 0
# define CELL_SIZE 32
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MAP_HEIGHT 10
# define MAP_WIDTH 10
# define PI 3.14159265359

# define RGBRED 0xFF0000
# define RGBGREEN 0x00FF00
# define RGBBLUE 0x0000FF
# define RGBDEFAULT 0xFFFF00 // Jaune


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

// typedef struct s_colorRGB
// {
//    int  r;
//    int  g;
//    int  b;
// } t_colorRGB;

typedef struct s_ray
{
	double	rayDirX;
	double	rayDirY;
	double	planeX;
	double	planeY;
	double	deltaDistX; // Distance to go through 1 case
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		dirX;
	int		dirY;
	int		stepX; // Step direction (-1 or 1)
	int		stepY;
	int		hit; // Hit a wall
	int		side; // Where the wall is hit
	int		FOV; // Field of view
}			t_ray;

typedef struct s_player
{
	double	x; // Player EXACT position
	double	y;
	int		mapX; // Player position (1 or 0)
	int		mapY;
	double	old_x; // Player previous exact position
	double	old_y;
	double	angle; // Player angle
}			t_player;


typedef struct s_game_data
{
	int			bpp; // Bits per pixel
	double		time; // Time of current frame
	double		oldTime; // Time if previous frame
	double		frameTime;
	double		moveSpeed;
	double		rotSpeed;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_color;
	char		*ceiling_color;
	char		**map;
	char		**file;
	void		*mlx;
	void		*win;
	void		*img;
	void		*player_img;
	char		*ray_img;
	char		*ray_addr;
	char		*img_addr;
	char		*player_addr;
	int			endian;
	int			line_length;
	t_ray		raycast;
	t_player	player;
}				t_game_data;

//Algo
void	image_init(t_game_data *game);
void	draw_map(t_game_data *game);
void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
void	game_data_init(t_game_data *game);
int		render_frame(t_game_data *game);
void	draw_player(t_game_data *game, double x, double y, int radius, int color);
void	raycasting(t_game_data *game);
void	digital_differential_analyzer(t_game_data *game, int x);
void	init_game(t_game_data *game);

//Exec
int		map_check(char **input);
int		check_lines(char **map);
int		count_lines(int fd);
int		check_file(char *input);
int		map_width(int index, char **input);
int		count_words(char *input);
int		check_walls(int width, int index, char **map);
int		check_start(char **map);
int		check_filling(char **map);
char	*open_file(char **av);
int		fill_map_struct(t_game_data *game, char **av);
void	fill_map(char **map, int length, int row, int column);
int		flood_fill(char **map);
int		get_map_index(char **file);
int		count_lines_map(char **file, int index);
char	**get_map(char **file, int index);
int		map_length(int index, char **input);
void	free_everything(char **s);
char	*get_file_texture(char *file);
int		textures(t_game_data *game, char *file);
int		get_textures(t_game_data *game, char **file);

#endif