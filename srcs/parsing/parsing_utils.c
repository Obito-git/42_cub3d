#include "cub3d.h"

bool	texture_addr_setter(t_data *data)
{
	t_textures	*t;

	t = &data->texture;
	data->texture.north.addr = mlx_get_data_addr(t->north.img, &t->north.bpp,
		&t->north.size_line, &t->north.endian);
	data->texture.south.addr = mlx_get_data_addr(t->south.img, &t->south.bpp,
		&t->south.size_line, &t->south.endian);
	data->texture.east.addr = mlx_get_data_addr(t->east.img, &t->east.bpp,
		&t->east.size_line, &t->east.endian);
	data->texture.west.addr = mlx_get_data_addr(t->west.img, &t->west.bpp,
		&t->west.size_line, &t->west.endian);
	return (1);
}

void	to_next_nbr(int *index, char *str)
{
	while (ft_isdigit(str[*index]) != 0 && str[*index])
		*index += 1;
	*index += 1;
	while (ft_isdigit(str[*index]) == 0 && str[*index])
		*index += 1;
}