#include "cub3d.h"

unsigned int	get_collum_color(t_rend_attr *ra, int j)
{
	if (j < ra->start)
		return (0x00FFFF);
	else if (j >= ra->start && j < ra->end)
	{
		if (ra->side == 0)
			return (0xFF6666);
		else if (ra->side == 1)
			return (0xFF9999);
		else if (ra->side == 2)
			return (0x6600CC);
		else
			return (0x404040);
	}
	else
		return (0x009900);
}

void	render_collum(t_rend_attr *ra, t_data *data)
{
	set_distance(ra, data);
	ra->line_height = (int)(HEIGHT / ra->dist);
	ra->start = -(ra->line_height) / 2 + HEIGHT / 2;
	if (ra->start < 0)
		ra->start = 0;
	ra->end = ra->line_height / 2 + HEIGHT / 2;
	if (ra->end >= HEIGHT)
		ra->end = HEIGHT - 1;
	int j = 0;
	while (j < HEIGHT)
	{
		*(unsigned int *)(data->img_p + (j * data->setup.size_line
			+ ra->column_numb * (data->setup.bpp / 8))) = get_collum_color(ra, j);
		j++;
	}
}

void	render(t_data *data)
{
	int			i;
	t_rend_attr	*rend_attr;

	rend_attr = (t_rend_attr *) malloc(sizeof(t_rend_attr));
	if (!rend_attr)
		return ;
	i = 0;
	while (i < WIDTH)
	{
		rend_attr->column_numb = i;
		render_collum(rend_attr, data);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_minimap(data);
	free(rend_attr);
}