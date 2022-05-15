/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:44 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:42:32 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_name(char *file_name)
{
	int	i;

	i = ft_strlen(file_name);
	if (i < 4)
		return (0);
	if (ft_strncmp(file_name + i - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

void	init_data_h(t_data *data)
{
	data->txtrs = malloc(sizeof(char *) * 4);
	if (data->txtrs == NULL)
	{
		ft_putstr_fd("cub3d: malloc issue.\n", 2);
		exit(1);
	}
	data->world_map = malloc(sizeof(char *) * 1);
	if (data->world_map == NULL)
	{
		ft_putstr_fd("cub3d: malloc issue.\n", 2);
		exit(1);
	}
	data->world_map[0] = NULL;
	data->txtrs[0] = NULL;
	data->txtrs[1] = NULL;
	data->txtrs[2] = NULL;
	data->txtrs[3] = NULL;
}

void	init_data(t_data *data)
{
	data->world_map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img.img = NULL;
	data->texture.north.img = NULL;
	data->texture.south.img = NULL;
	data->texture.east.img = NULL;
	data->texture.west.img = NULL;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
	init_data_h(data);
}

/*
void	print_data(t_data data)
{
	int i;

	printf("\n___TEXTURES_PATHS:___\n");
	i = 0;
	while (i < 4)
	{
		if (data.txtrs[i])
			printf("%s\n", data.txtrs[i]);
		i++;
	}
	
	printf("\n___COLORS:___\n");
	printf("  sky_colors = %X \n", data.img.sky_color);
	printf("floor_colors = %X \n", data.img.floor_color);

	printf("\n___PLAYER:___\n");
	printf("player   position: [%f][%f]\n", data.player.pos.x, data.player.pos.y);
	printf("player  direction: [%f][%f]\n", data.player.dir.x, data.player.dir.y);
	printf("player cam vector: [%f][%f]\n", data.player.cam.x, data.player.cam.y);

	printf("\n___MAP:___\n");
	i = 0;
	while (data.world_map[i])
	{
		printf("<%s>\n", data.world_map[i]);
		i++;
	}
}
*/
