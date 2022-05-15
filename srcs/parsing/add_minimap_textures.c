/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_minimap_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:58 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:14:17 by lnelson          ###   ########.fr       */
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
