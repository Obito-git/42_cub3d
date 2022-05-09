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
	if (data->map != NULL)
	{
		i = 0;
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
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
	temp = data->map;
	while (temp[size])
		size++;
	data->map = malloc(sizeof(char *) * (size + 2));
	if (data->map == NULL)
		return (0);
	data->map[size] = ft_strdup(line);
	if (data->map[size] == NULL)
		return (0);
	data->map[size + 1] = NULL;
	size = 0;
	while (temp[size])
	{
		data->map[size] = temp[size];
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
		tmp = data->setup.floor_c;
	else
		tmp = data->setup.floor_c;
	tmp[0] = (unsigned char)ft_atoi(temp + i);
	while (ft_isdigit(temp[i]) == 0 && temp[i])
		i++;
	if (temp[i] == 0)
		return 0;;
	tmp[1] = (unsigned char)ft_atoi(temp + i);
	while (ft_isdigit(temp[i]) == 0 && temp[i])
		i++;
	if (temp[i] == 0)
		return 0;;
	tmp[2] = (unsigned char)ft_atoi(temp + i);
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

	ret = 1;
	while (get_next_line(fd, &temp) != 0 && ret != 0)
	{
		parsing_helper(data, temp, &ret);
		free(temp);
		temp = NULL;
	}
	parsing_helper(data, temp, &ret);
	free(temp);
	temp = NULL;
	if (ret == 0)
		exit_parser(data, &temp, fd);
}