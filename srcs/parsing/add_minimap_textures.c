#include "cub3d.h"

bool	add_minimap_textures(t_data *data)
{
	int	bs;
	int	ws;

	bs = 120;
	ws = 10;
	data->texture.minimap_border = mlx_xpm_file_to_image(data->mlx,
		"./textures/minimap_border.xpm", &bs, &bs);
	if (!data->texture.minimap_border)
		return (false);
	data->texture.minimap_wall = mlx_xpm_file_to_image(data->mlx,
		"./textures/minimap_wall.xpm", &ws, &ws);
	if (!data->texture.minimap_wall)
		return (false);
	data->texture.minimap_player = mlx_xpm_file_to_image(data->mlx,
		"./textures/minimap_player.xpm", &ws, &ws);
	if (!data->texture.minimap_player)
		return (false);
	return (true);
}