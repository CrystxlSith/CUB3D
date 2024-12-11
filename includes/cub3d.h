#ifndef CUB3D_H
# define CUB3D_H

# define FLOOR_HORIZONTAL 1
# define TRUE 1
# define FALSE 0
# define CELL_SIZE 32
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MAP_HEIGHT 10
# define MAP_WIDTH 10
# define PI 3.14159265359


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
# include <sys/time.h>

typedef struct s_ray
{
	double	raydirx;
	double	raydiry;
	double	planex;
	double	planey;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	double	posx;
	double	posy;
	double	posz;
	double	perpwalldist;
	double	time;
	double	oldtime;
	double	delta_time;
	double	dirx;
	double	diry;
	double	pitch;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		texnum;
	double	wallx;
	int		texx;
	int		texy;
	int		line_height;
}			t_ray;

typedef struct s_key
{
	int		forward;
	int		backward;
	int		turn_left;
	int		turn_right;
	int		escape;
}			t_key;

typedef struct s_player
{
	double	x;
	double	y;
	int		mapx;
	int		mapy;
	double	old_x;
	double	old_y;
	double	angle;
}			t_player;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}			t_texture;

typedef struct s_game_data
{
	int			bpp;
	double		movespeed;
	double		rotspeed;
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
	t_key		key;
	t_ray		raycast;
	t_player	player;
	t_texture	textures[4];
}				t_game_data;

// ----------------------------------------------------------------------
// 									ALGO
// ----------------------------------------------------------------------

//draw.c
void	draw_map(t_game_data *game);
void	my_mlx_pixel_put(t_game_data *data, int x, int y, int color);
void	draw_player(t_game_data *game, double x, \
	double y, int radius, int color);
void	draw_floor_and_ceiling(t_game_data *game);

//draw_utils.c
void	draw_floor_and_ceiling(t_game_data *game);

//render.c
int		render_frame(t_game_data *game);
void	update_player(t_game_data *game);

//raycast.c
void	raycasting(t_game_data *game);

//raycast_utils.c
void	fps_count(t_game_data *game);
double	get_time_in_seconds(void);

//dda.c
void	draw_raycast(t_game_data *game, int x);
void	digital_differential_analyzer(t_game_data *game, int x);

// movement.c
void	move_back(t_game_data *game, double movespeed);
void	move_front(t_game_data *game, double movespeed);
void	turn_right(t_game_data *game, double rotation_speed);
void	turn_left(t_game_data *game, double rotation_speed);
void	through_door(t_game_data *game, double newposx, double newposy);

//handle_input.c
int		handle_input(int keycode, t_game_data *game);
int		input_release(int keycode, t_game_data *game);
int		close_game(t_game_data *game);
int		handle_mouse_motion(int x, int y, t_game_data *game);

// init.c
void	init_game(t_game_data *game);
void	ft_mlx_init(t_game_data *game);
void	image_init(t_game_data *game);
void	image_init2(t_game_data *game);
void	init_game2(t_game_data *game);

// ----------------------------------------------------------------------
// 									PARSING
// ----------------------------------------------------------------------

//open_map.c
char	*open_file(char **av);
int		fill_map_struct(t_game_data *game, char **av);
int		get_map_index(char **file);
int		count_lines_map(char **file, int index);
char	**get_map(char **file, int index);

//get_colors.c
char	*get_file_color(char *file);
int		get_colors(t_game_data *game, char *file);
int		open_texture(char *texture);

//get_textures.c
int		get_textures(t_game_data *game, char **file);
char	*get_file_texture(char *file);
int		textures(t_game_data *game, char *file);

//map_check.c
int		map_check(t_game_data *game);
int		check_lines(t_game_data *game);
int		count_lines(int fd);
int		check_file(char *input);
void	free_everything(char **s);

//map_dimensions.c
int		map_width(int index, char **input);
int		count_words(char *input);
int		map_length(int index, char **input);

//map_rules.c
int		check_walls(int width, int index, char **map);

//map_rules2.c
int		check_start(t_game_data *game);
int		check_filling(char **map);

#endif