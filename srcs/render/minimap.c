#include "cub3d.h"

void draw_line(t_data *data, t_vector_2d start, t_vector_2d end, int color)
{
	double deltaX;
	double deltaY;
	int pixels;

	deltaX = (end.x - start.x);
	deltaY = (end.y - start.y);
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
   		mlx_pixel_put(data->mlx, data->win, start.x, start.y, color);
    	start.x += deltaX;
    	start.y += deltaY;
    	--pixels;
	}
}

void	draw_player(t_data *data, int offset)
{
	//mlx_string_put(data->mlx, data->win, 50, 50, 322, "P");
	float	pdx;
	float	pdy;
	float	pa;
	int		minimap_pp;

	minimap_pp = 50 + offset / 2;
	mlx_put_image_to_window(data->mlx, data->win, data->texture.minimap_player, minimap_pp, minimap_pp);
	pa = atan2(data->player.dir.y, data->player.dir.x);
	pdy = cos(pa);
	pdx = sin(pa);
	minimap_pp += offset / 3;
	draw_line(data, create_vector(minimap_pp, minimap_pp),
		create_vector(minimap_pp + pdx * 14, minimap_pp + pdy * 14), 0xDC143C);
}

void	draw_wall_iteration(int *i, int *y, int *row, int *column)
{
	*y = 0;
	while (*row < 0)
	{
		*row += 1;
		*i += 1;
	}
	while (*column < 0)
	{
		*column += 1;
		*y += 1;
	}
}

void	draw_wall(t_data *data, int offset)
{
	int	row;
	int	column;
	int i;
	int y;

	i = 0;
	row = (int)data->player.pos.x - 4;
	while (row < (int)data->player.pos.x + 5)
	{
		column = (int)data->player.pos.y - 4;
		draw_wall_iteration(&i, &y, &row, &column);
		if (!data->map[row])
			break;
		while (column < (int)data->player.pos.y + 5 && data->map[row][column])
		{
			if (data->map[row][column] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->texture.minimap_wall,
					y * 10 + offset, i * 10 + offset);
			column++;
			y++;
		}
		row++;
		i++;
	}
}

void	render_minimap(t_data *data)
{
	int	offset;

	offset = 15;
	mlx_put_image_to_window(data->mlx, data->win, data->texture.minimap_border, 0, 0);
	draw_player(data, offset);
	draw_wall(data, offset);
}