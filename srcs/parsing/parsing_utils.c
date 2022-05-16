/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:53 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/11 16:54:45 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	check_player_count(char **s)
{
	int	count;
	int	i;
	int	y;

	y = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[y])
	{
		i = 0;
		while (s[y][i])
		{
			if (ft_isalpha(s[y][i]))
				count++;
			i++;
		}
		y++;
	}
	return (1);
}

char	texture_addr_setter(t_data *data)
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

void	set_cam_vector(t_data *data)
{
	data->player.cam.x = data->player.dir.y;
	data->player.cam.y = -(data->player.dir.x);
}

void	exit_parser(t_data *data, char **temp, int fd)
{
	int	i;

	i = 0;
	while (get_next_line(fd, temp) != 0)
		free(*temp);
	free(*temp);
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
	ft_putstr_fd("cub3d: parsing error, check your file format.\n", 2);
	exit (1);
}
