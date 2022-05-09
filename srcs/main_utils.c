#include "cub3d.h"

int	check_file_name(char *file_name)
{
	int i;

	i = ft_strlen(file_name);
	if (i < 4)
		return (0);
	if (ft_strncmp(file_name + i - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

void	init_data(t_data *data)
{
	data->world_map = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->texture.north = NULL;
	data->texture.south = NULL;
	data->texture.est = NULL;
	data->texture.west = NULL;
	data->player.pos.x = -1;
	data->player.pos.y = -1;
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
	printf("  sky_colors = %i | %i | %i \n", data.setup.sky_c[0], data.setup.sky_c[1], data.setup.sky_c[2]);
	printf("floor_colors = %i | %i | %i \n", data.setup.floor_c[0], data.setup.floor_c[1], data.setup.floor_c[2]);

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
