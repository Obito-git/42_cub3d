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
	while (data->map[i])
	{
		if(ft_strlen(data->map[i]) > max_size)
			max_size = ft_strlen(data->map[i]);
		i++;
	}
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) < max_size)
		{
			temp = data->map[i];
			data->map[i] = add_n_c(temp, max_size - ft_strlen(data->map[i]));
			free(temp);		
		}
		i++;
	}
	return (1);
}

int		check_node(t_data *data, int i, int j)
{
	if (i == 0 || data->map[i + 1] == NULL)
	{
		if (data->map[i][j] != '1')
			return (0);
	}
	else if (data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' ')
	{
		//printf("\ndata->map[i] = %s\n data->[i][j] = <%c> \n i = %i | j = %i |\ndata->map[i - 1][j] = <%c> | data->map[i + 1][j] = <%c>\n", data->map[i], data->map[i][j], i, j, data->map[i - 1][j], data->map[i + 1][j]);
		return (0);
	}
	return (1);
}

void	add_p_pos(t_data *data, int x, int y)
{
	if (data->player.pos.x != -1)
		return ;
	data->player.pos.x = (float)x;
	data->player.pos.y = (float)y;
	if (data->map[x][y] == 'N')
	{
		data->player.dir.x = 1;
		data->player.dir.y = 0; 
	}	
	else if (data->map[x][y] == 'S')
	{
		data->player.dir.x = -1;
		data->player.dir.y = 0;
	}
	else if (data->map[x][y] == 'E')
	{
		data->player.dir.x = 0;
		data->player.dir.y = 1;
	}
	else if (data->map[x][y] == 'W')
	{
		data->player.dir.x = 0;
		data->player.dir.y = -1;
	}
}

void	set_cam_vector(t_data *data)
{
	data->player.cam.x = data->player.dir.y;
	data->player.cam.y = -(data->player.dir.x);
}

int	map_processing(t_data *data)
{
	int i;
	int j;

	expand_map(data);
	if (!data->map[1])
		return (-1);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != '1' && data->map[i][j] != ' ')
			{
				if (check_node(data, i, j) == 0)
					return (ret_error("cub3d: file have holes.\n", -1));
			}
			if (ft_strrchr("NSEW", data->map[i][j]) != NULL)
				add_p_pos(data, i, j);
			j++;
		}
		i++;
	}
	set_cam_vector(data);
	return ((int)(data->player.pos.x));
}