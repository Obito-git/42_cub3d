/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:56 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:09:44 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_north_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != ' ' && temp[i])
		i++;
	while (temp[i] == ' ')
		i++;
	if (temp[i] == 0)
	{
		ft_putstr_fd("cub3d: textures line - filename_missing", 2);
		return (0);
	}
	(data->txtrs)[NORTH_T] = ft_strdup(temp + i);
	if (data->txtrs[NORTH_T] == NULL)
	{
		ft_putstr_fd("cub3d: malloc issued", 2);
		return (0);
	}
	return (1);
}

int	add_south_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != ' ' && temp[i])
		i++;
	while (temp[i] == ' ')
		i++;
	if (temp[i] == 0)
	{
		ft_putstr_fd("cub3d: textures line - filename_missing", 2);
		return (0);
	}
	data->txtrs[SOUTH_T] = ft_strdup(temp + i);
	if (data->txtrs[SOUTH_T] == NULL)
	{
		ft_putstr_fd("cub3d: malloc issued", 2);
		return (0);
	}
	return (1);
}

int	add_east_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != ' ' && temp[i])
		i++;
	while (temp[i] == ' ')
		i++;
	if (temp[i] == 0)
	{
		ft_putstr_fd("cub3d: textures line - filename_missing", 2);
		return (0);
	}
	data->txtrs[EAST_T] = ft_strdup(temp + i);
	if (data->txtrs[EAST_T] == NULL)
	{
		ft_putstr_fd("cub3d: malloc issued", 2);
		return (0);
	}
	return (1);
}

int	add_west_texture(t_data *data, char *temp)
{
	int	i;

	i = 0;
	while (temp[i] != ' ' && temp[i])
		i++;
	while (temp[i] == ' ')
		i++;
	if (temp[i] == 0)
	{
		ft_putstr_fd("cub3d: textures line - filename_missing", 2);
		return (0);
	}
	data->txtrs[WEST_T] = ft_strdup(temp + i);
	if (data->txtrs[WEST_T] == NULL)
	{
		ft_putstr_fd("cub3d: malloc issued", 2);
		return (0);
	}
	return (1);
}

int	get_textures(t_data *data)
{
	int	i;
	int	p;

	p = 64;
	i = 0;
	data->texture.north.img = mlx_xpm_file_to_image(data->mlx, (data->txtrs)[0],
			&p, &p);
	data->texture.south.img = mlx_xpm_file_to_image(data->mlx, (data->txtrs)[1],
			&p, &p);
	data->texture.west.img = mlx_xpm_file_to_image(data->mlx, (data->txtrs)[2],
			&p, &p);
	data->texture.east.img = mlx_xpm_file_to_image(data->mlx, (data->txtrs)[3],
			&p, &p);
	p = 100;
	if (data->texture.east.img == NULL || data->texture.north.img == NULL
		|| data->texture.west.img == NULL || data->texture.south.img == NULL
		|| !add_minimap_textures(data) || !texture_addr_setter(data))
		return (0);
	while (i < 4)
	{
		free(data->txtrs[i]);
		data->txtrs[i] = NULL;
		i++;
	}
	return (1);
}
