#ifndef CUB3D_H
# define CUB3D_H

/*######################################################*/
/*						INLCUDES						*/
/*######################################################*/

# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>

# include "keycodes_linux.h"
# include "2d_ftmath.h"
# include "libft.h"
# include "mlx.h"

/*######################################################*/
/*						DEFINES							*/
/*######################################################*/

# define NORTH_T 0
# define SOUTH_T 1 
# define EAST_T 2
# define WEST_T 3

# define WIDTH 1280
# define HEIGHT 720

# define _PI_ 3.14159265358979323846
/*######################################################*/
/*						STRUCTS							*/
/*######################################################*/

typedef	struct	s_rend_attr
{
	t_2vector	vector;
	int			column_numb;
	int			side;
	float		dist;
	float		sideDistX;
	float		sideDistY;
	float		deltaDistX;
	float		deltaDistY;
	int			stepX;
	int			stepY;
	int			currentX;
	int			currentY;
	int			line_height;
	int			start;
	int			end;
	char		orient;	
}				t_rend_attr;


typedef	struct	s_player
{
	t_2vector	pos;
	t_2vector	dir;
	t_2vector	cam;
}				t_player;

typedef	struct	s_textures
{
	void	*north;
	void	*south;
	void	*est;
	void	*west;
	void	*minimap_border;
	void	*minimap_wall;
	void	*minimap_player;
}				t_textures;

typedef struct	s_cub3d
{
	int				bpp;
	int				size_line;
	int				endian;
	char			**map;
	char			**txtrs;
	unsigned char	floor_c[3];
	unsigned char	sky_c[3];
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_p;
	t_textures		texture;
	t_player		player;
}				t_data;

/*######################################################*/
/*						FUNCTIONS						*/
/*######################################################*/

/*	MAIN.C				*/

/* KEY_HOOKS.C			*/

int		key_hooks(int keycode, t_data *data);
void	turn(int keycode, t_data *data);
int		mouse_handler(int x, int y, void *param);

/*	MAIN_UTILS.C		*/

int		starter(int ac, char **av, t_data *data);
int		check_file_name(char *file_name);
void	init_data(t_data *data);
void	print_data(t_data data);

/*	EXITS.C				*/

int		ret_error(char *str, char ret_value);
void	free_mlx(t_data *data);
int		ft_exit(t_data *data);

/*	ADD_TEXTURES.C		*/

int		add_north_texture(t_data *data, char *temp);
int		add_south_texture(t_data *data, char *temp);
int		add_east_texture(t_data *data, char *temp);
int		add_west_texture(t_data *data, char *temp);
int		get_textures(t_data *data);

/*	ADD_MINIMAP_TEXTURES.C		*/
bool	add_minimap_textures(t_data *data);

/*	PARSING.C			*/

void	exit_parser(t_data *data, char **temp, int fd);
int		check_map_line(char *map_line);
int		add_map_line(t_data *data, char *line);
int		add_colors(t_data *data, char *temp);
void	parsing_helper(t_data *data, char *temp, int *ret);
void	parsing(t_data *data, int fd);

/*	MAP_PROCESSING		*/

char	*add_n_c(char *str1, int n);
int		expand_map(t_data *data);
int		check_node(t_data *data, int i, int j);
void	add_p_pos(t_data *data, int x, int y);
void	set_cam_vector(t_data *data);
int		map_processing(t_data *data);

/*	RENDER.C			*/

void	render(t_data *data);

/*minimap.c*/
void	render_minimap(t_data *data);

/*	CALCULATIONS.C		*/
void	set_side_dist(t_rend_attr *ra, t_data *data);
void	set_side_dist_helper(t_rend_attr *ra, t_data *data);
void	set_distance(t_rend_attr *ra, t_data *data);


#endif