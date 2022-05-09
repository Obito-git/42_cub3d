#include "cub3d.h"

int	ret_error(char *str, char ret_value)
{
	ft_putstr_fd(str, 2);
	return (ret_value);
}

void	free_mlx(t_data *data)
{
	if (data->texture.north != NULL)
		mlx_destroy_image(data->mlx, data->texture.north);
	if (data->texture.south != NULL)
		mlx_destroy_image(data->mlx, data->texture.south);
	if (data->texture.est != NULL)
		mlx_destroy_image(data->mlx, data->texture.est);
	if (data->texture.west != NULL)
		mlx_destroy_image(data->mlx, data->texture.west);
	if (data->texture.minimap_border)
		mlx_destroy_image(data->mlx, data->texture.minimap_border);
	if (data->texture.minimap_wall)
		mlx_destroy_image(data->mlx, data->texture.minimap_wall);
	if (data->texture.minimap_player)
		mlx_destroy_image(data->mlx, data->texture.minimap_player);
	if (data->mlx != NULL)
	{
		if (data->img != NULL)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	ft_exit(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data->txtrs[i] != NULL)
			free(data->txtrs[i]);
		i++;
	}
	free(data->txtrs);
	if (data->world_map != NULL)
	{
		i = 0;
		while (data->world_map[i])
			free(data->world_map[i++]);
		free(data->world_map);
	}
	free_mlx(data);
	exit (0);
	return (1);
}
