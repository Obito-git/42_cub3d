/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:05 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:38:21 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h>

# include "keycodes_linux.h"
# include "ft_math2d.h"
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
# define TEXTURE_SIZE 64

# define _PI_ 3.14159265358979323846
/*######################################################*/
/*						STRUCTS							*/
/*######################################################*/

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		floor_color;
	int		sky_color;
}	t_image;

typedef struct s_player
{
	t_2vector	pos;
	t_2vector	dir;
	t_2vector	cam;
}	t_player;

typedef struct s_textures
{
	t_image		north;
	t_image		west;
	t_image		south;
	t_image		east;
	void		*minimap_border;
	void		*minimap_wall;
	void		*minimap_player;
}	t_textures;

typedef struct s_ray
{
	t_2point	wall;
	t_2point	texture;
	t_2point	current_pixel;
	t_2vector	ray_dir;
	t_2vector	side_distance;
	t_2vector	delta_distance;
	t_2vector	step;
	t_2vector	map;
	t_2vector	camera;
	t_2vector	*plane;
	float		perp_wall_dist;
	int			side;
	bool		hit;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			texture_step;
	double		texture_pos;
}	t_ray;

typedef struct s_cub3d
{
	char			**world_map;
	char			**txtrs;
	void			*mlx;
	void			*win;
	t_image			img;
	t_textures		texture;
	t_player		player;
}	t_data;

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
bool	texture_addr_setter(t_data *data);
void	to_next_nbr(int *index, char *str);

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
void	set_side_dist(t_data *data, t_ray *ray);
void	set_side_dist_helper(t_data *data, t_ray *ray);
void	set_distance(t_data *data, t_ray *ray);
void	set_texture_position(t_data *data, t_ray *ray);

#endif
