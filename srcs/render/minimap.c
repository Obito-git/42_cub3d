#include "cub3d.h"

void	draw_player(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 50, 50, 322, "P");
}

void	draw_wall(t_data *data)
{
	int	row;
	int	column;
	int i;
	int y;

	i = 0;
	row = (int)data->player.pos.x - 4;
	while (row < (int)data->player.pos.x + 5 && data->map[row])
	{
		y = 0;
		column = (int)data->player.pos.y - 4;
		while (row < 0)
		{
			row++;
			i++;
		}
		while (column < 0)
		{
			column++;
			y++;
		}
		while (column < (int)data->player.pos.y + 5 && data->map[row][column])
		{
			if (data->map[row][column] == '1')
				mlx_string_put(data->mlx, data->win, y * 10 + 10, i * 10 + 10, 322, "1");
			column++;
			y++;
		}
		row++;
		i++;
	}
}

void	render_minimap(t_data *data)
{
	draw_player(data);
	draw_wall(data);
}