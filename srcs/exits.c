/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:05:57 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:06:47 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ret_error(char *str, char ret_value)
{
	ft_putstr_fd(str, 2);
	return (ret_value);
}

void	free_mlx(t_data *data)
{
	if (data->texture.north.img != NULL)
		mlx_destroy_image(data->mlx, data->texture.north.img);
	if (data->texture.south.img != NULL)
		mlx_destroy_image(data->mlx, data->texture.south.img);
	if (data->texture.east.img != NULL)
		mlx_destroy_image(data->mlx, data->texture.east.img);
	if (data->texture.west.img != NULL)
		mlx_destroy_image(data->mlx, data->texture.west.img);
	if (data->texture.minimap_border)
		mlx_destroy_image(data->mlx, data->texture.minimap_border);
	if (data->texture.minimap_wall)
		mlx_destroy_image(data->mlx, data->texture.minimap_wall);
	if (data->texture.minimap_player)
		mlx_destroy_image(data->mlx, data->texture.minimap_player);
	if (data->mlx != NULL)
	{
		if (data->img.img != NULL)
			mlx_destroy_image(data->mlx, data->img.img);
		if (data->win != NULL)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	ft_exit(t_data *data)
{
	int	i;

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
