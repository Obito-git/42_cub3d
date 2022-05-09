#include "cub3d.h"

void	put_pixel_image(t_data data, int x, int y, int color)
{
	*(unsigned int *)
	(data.img_p + 
	(x * data.setup.size_line +
	 y * (data.setup.bpp / 8)))	= color;
}

void	render_collum(t_data *data, int x)
{
	int start, end, line_height; // ?? need to put in struct?
	set_distance(data, x);
	line_height = (int)(HEIGHT / data->perpWallDist);
	start = -(line_height) / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
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