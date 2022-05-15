/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:55 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:12:03 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*add_n_c(char *str1, int n)
{
	char	*temp;
	int		i;
	char	*ret;

	ret = NULL;
	temp = malloc(sizeof(char) * (n + 1));
	i = 0;
	while (i < n)
	{
		temp[i] = ' ';
		i++;
	}
	temp[i] = 0;
	ret = ft_strjoin(str1, temp);
	free(temp);
	return (ret);
}

int	expand_map(t_data *data)
{
	int		i;
	int		max_size;
	char	*temp;

	i = 0;
	max_size = 0;
	while (data->world_map[i])
	{
		if (ft_strlen(data->world_map[i]) > max_size)
			max_size = ft_strlen(data->world_map[i]);
		i++;
	}
	i = 0;
	while (data->world_map[i])
	{
		if (ft_strlen(data->world_map[i]) < max_size)
		{
			temp = data->world_map[i];
			data->world_map[i] = add_n_c(temp, max_size
					- ft_strlen(data->world_map[i]));
			free(temp);
		}
		i++;
	}
	return (1);
}

int	check_node(t_data *data, int i, int j)
{
	if (i == 0 || data->world_map[i + 1] == NULL)
	{
		if (data->world_map[i][j] != '1')
			return (0);
	}
	else if (data->world_map[i - 1][j] == ' '
		|| data->world_map[i + 1][j] == ' ')
		return (0);
	return (1);
}

void	add_p_pos(t_data *data, int x, int y)
{
	if (data->player.pos.x != -1)
		return ;
	data->player.pos.x = (float)x + 0.5;
	data->player.pos.y = (float)y + 0.5;
	if (data->world_map[x][y] == 'N')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0;
	}	
	else if (data->world_map[x][y] == 'S')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
	}
	else if (data->world_map[x][y] == 'E')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
	}
	else if (data->world_map[x][y] == 'W')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
	}
}

int	map_processing(t_data *data)
{
	int	i;
	int	j;

	expand_map(data);
	if (!data->world_map[1])
		return (-1);
	i = 0;
	while (data->world_map[i])
	{
		j = 0;
		while (data->world_map[i][j])
		{
			if (data->world_map[i][j] != '1' && data->world_map[i][j] != ' ')
			{
				if (check_node(data, i, j) == 0)
					return (ret_error("cub3d: file have holes.\n", -1));
			}
			if (ft_strrchr("NSEW", data->world_map[i][j]) != NULL)
				add_p_pos(data, i, j);
			j++;
		}
		i++;
	}
	set_cam_vector(data);
	return ((int)(data->player.pos.x));
}
