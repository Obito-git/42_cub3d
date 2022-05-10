#include "cub3d.h"

void	exit_parser(t_data *data, char **temp, int fd)
{
	int i;

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

int	check_map_line(char *map_line)
{
	int i;

	i = 0;
	while (map_line[i] == ' ' || map_line[i] == '\t')
		i++;
	if (map_line[i] != '1' && map_line[ft_strlen(map_line) - 1] != '1')
		return (0);
	while (map_line[i])
	{
		if (ft_strchr("01 NSEW", map_line[i]) == NULL)
			return (0);
		if (map_line[i] == ' ')
		{
			if (map_line[i - 1] != '1')
				return (0);
			while (map_line[i] == ' ')
				i++;
			if (map_line[i] != 0 && map_line[i] != '1')
				return (0);
		}
		i++;
	}
	return (1);
}

int	add_map_line(t_data *data, char *line)
{
	char	**temp;
	int		size;

	if (check_map_line(line) == 0)
		return (0);
	size = 0;
	temp = data->world_map;
	while (temp[size])
		size++;
	data->world_map = malloc(sizeof(char *) * (size + 2));
	if (data->world_map == NULL)
		return (0);
	data->world_map[size] = ft_strdup(line);
	if (data->world_map[size] == NULL)
		return (0);
	data->world_map[size + 1] = NULL;
	size = 0;
	while (temp[size])
	{
		data->world_map[size] = temp[size];
		size++;
	}
	free(temp);
	return (1);
}

int	add_colors(t_data *data, char *temp)
{
	int				i;
	unsigned char	*tmp;

	i = 0;
	while (ft_isdigit(temp[i]) == 0 && temp[i])
		i++;
	if (temp[i] == 0)
		return 0;
	if (temp[0] == 'F')
		tmp = (unsigned char *)(&(data->img.floor_color));
	else
		tmp = (unsigned char *)(&(data->img.sky_color));
	tmp[0] = (unsigned char)ft_atoi(temp + i);
															ft_putnbr_fd(ft_atoi(temp + i), 1);
															write(1, "\n", 1);
	to_next_nbr(&i, temp);
	if (temp[i] == 0)
		return 0;
	tmp[1] = (unsigned char)ft_atoi(temp + i);
															ft_putnbr_fd(ft_atoi(temp + i), 1);
															write(1, "\n", 1);
	to_next_nbr(&i, temp);
	if (temp[i] == 0)
		return 0;
	tmp[2] = (unsigned char)ft_atoi(temp + i);
															ft_putnbr_fd(ft_atoi(temp + i), 1);
															write(1, "\n", 1);
	return (1);
}

void		parsing_helper(t_data *data, char *temp, int *ret)
{
	if (temp[0] == 'N' && temp[1] == 'O')
		*ret = add_north_texture(data, temp);
	else if (temp[0] == 'S' && temp[1] == 'O')
		*ret = add_south_texture(data, temp);
	else if (temp[0] == 'E' && temp[1] == 'A')
		*ret = add_east_texture(data, temp);
	else if (temp[0] == 'W' && temp[1] == 'E')
		*ret = add_west_texture(data, temp);
	else if (temp[0] == 'F' || temp[0] == 'C')
		*ret = add_colors(data, temp);
	else if (temp[0] != 0)
		*ret = add_map_line(data, temp);
}

void	parsing(t_data *data, int fd)
{
	char	*temp;
	int		ret;

	data->texture.minimap_border = NULL;
	data->texture.minimap_wall = NULL;
	data->texture.minimap_player = NULL;
	ret = 1;
	while (get_next_line(fd, &temp) != 0 && ret != 0)
	{
		parsing_helper(data, temp, &ret);
		free(temp);
		temp = NULL;
		if (ret == 0)
			exit_parser(data, &temp, fd);
	}
	parsing_helper(data, temp, &ret);
	free(temp);
	temp = NULL;
}