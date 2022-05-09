#include "cub3d.h"

unsigned int	get_collum_color(t_data *data, int j, int start, int end)
{
	if (j < start)
		return (0x00FFFF);
	else if (j >= start && j < end)
	{
		if (data->side == 0)
			return (0xFF6666);
		else if (data->side == 1)
			return (0xFF9999);
		else if (data->side == 2)
			return (0x6600CC);
		else
			return (0x404040);
	}
	else
		return (0x009900);
}

void	render_collum(t_data *data, int x)
{
	int start, end, line_height;
	set_distance(data, x);
	line_height = (int)(HEIGHT / data->perpWallDist);
	start = -(line_height) / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	int j = 0;
	while (j < HEIGHT)
	{
		*(unsigned int *)(data->img_p + (j * data->setup.size_line
			+ x * (data->setup.bpp / 8))) = get_collum_color(data, j, start, end);
		j++;
	}
}

void	render(t_data *data)
{
	int	x;

	x = 0;
	data->plane = &data->player.cam;
	while (x < WIDTH)
	{
		data->hit = false;
		render_collum(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_minimap(data);
}