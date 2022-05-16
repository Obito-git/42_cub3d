/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_and_minimap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:58 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/16 16:04:53 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	add_minimap_textures(t_data *data)
{
	int	bs;
	int	ws;

	bs = 120;
	ws = 10;
	data->texture.minimap_border = mlx_xpm_file_to_image(data->mlx,
			"./textures/minimap_border.xpm", &bs, &bs);
	if (!data->texture.minimap_border)
		return (0);
	data->texture.minimap_wall = mlx_xpm_file_to_image(data->mlx,
			"./textures/minimap_wall.xpm", &ws, &ws);
	if (!data->texture.minimap_wall)
		return (0);
	data->texture.minimap_player = mlx_xpm_file_to_image(data->mlx,
			"./textures/minimap_player.xpm", &ws, &ws);
	if (!data->texture.minimap_player)
		return (0);
	return (1);
}

int	ft_strcmp(char	*s1, char	*s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	is_correct_number(char *s, int *i)
{
	int		y;
	char	*tmp;

	y = *i;
	while (ft_isdigit(s[*i]))
		*i += 1;
	if (*i - y < 1 || *i - y > 3)
		return (0);
	if (*i - y == 3)
	{
		tmp = ft_strdup(&s[y]);
		if (!tmp)
			return (0);
		tmp[3] = 0;
		if (ft_strcmp("255", tmp) < 0)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
	}
	return (s[*i] == ',' || !s[*i]);
}

int	is_correct_color_pattern(char *s)
{
	int	i;
	int	nb_count;

	i = 1;
	nb_count = 0;
	while (s[i])
	{
		if (nb_count > 3)
			return (0);
		while (s[i] == ' ')
			i++;
		if (!is_correct_number(s, &i))
			return (0);
		nb_count++;
		if (s[i] == ',' && nb_count != 3)
			i++;
	}
	return (1);
}
