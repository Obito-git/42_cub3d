#include "cub3d.h"

//here is potential bug. check https://lodev.org/cgtutor/raycasting.html
void	set_side_dist(t_rend_attr *ra, t_data *data) 
{
	if (ra->vector.x < 0)
	{
		ra->sideDistX = (float)(data->player.pos.x -
			(int)data->player.pos.x) * ra->deltaDistX;
		ra->stepX = -1;
	}
	else
	{
		ra->sideDistX = (float)((int)data->player.pos.x + 1 -
			data->player.pos.x) * ra->deltaDistX;
		ra->stepX = 1;
	}
	if (ra->vector.y < 0)
	{
		ra->sideDistY = (float)(data->player.pos.y -
			(int)data->player.pos.y) * ra->deltaDistY;
		ra->stepY = -1;
	}
	else
	{
		ra->sideDistY = (float)((int)data->player.pos.y + 1 -
			data->player.pos.y) * ra->deltaDistY;
		ra->stepY = 1;
	}
}

void	set_distance_helper(t_rend_attr *ra, t_data *data)
{
	while (true)
	{
		if (ra->sideDistX < ra->sideDistY)
		{
			ra->sideDistX += ra->deltaDistX;
			ra->currentX += ra->stepX;
			ra->side = 0;
		}
		else
		{
			ra->sideDistY += ra->deltaDistY;
			ra->currentY += ra->stepY;
			ra->side = 2;
		}
		if (data->map[ra->currentX][ra->currentY] == '1')
			break ;
	}
	if (ra->side == 0 && ra->vector.x < 0)
		ra->side = 1;
	if (ra->side == 2 && ra->vector.y < 0)
		ra->side = 3;
	if (ra->side == 0 || ra->side == 1)
		ra->dist = (ra->currentX - data->player.pos.x + (1 - (double) ra->stepX) / 2) / ra->vector.x;
	else
		ra->dist = (ra->currentY - data->player.pos.y + (1 - (double) ra->stepY) / 2) / ra->vector.y;
}

void	set_distance(t_rend_attr *ra, t_data *data)
{
	ra->vector = add_vectors(data->player.dir, 
		scalar_mult(data->player.cam, ((2 * ra->column_numb) / (float)WIDTH) -1));
	if (ra->vector.x == 0)
		ra->deltaDistX = __FLT_MAX__;
	else
		ra->deltaDistX = sqrtf(1 + (powf(ra->vector.y,2) / powf(ra->vector.x, 2)));
	if (ra->vector.y == 0)
		ra->deltaDistY = __FLT_MAX__;
	else
		ra->deltaDistY = sqrtf(1 + (powf(ra->vector.x,2) / powf(ra->vector.y, 2)));
	ra->currentX = (int)data->player.pos.x;
	ra->currentY = (int)data->player.pos.y;
	set_side_dist(ra, data);
	set_distance_helper(ra, data);
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
		if (j < ra->start)
			*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0x00FFFF;
		else if (j >= ra->start && j < ra->end)
		{
			if (ra->side == 0)
				*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0xFF6666;
			else if (ra->side == 1)
				*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0xFF9999;
			else if (ra->side == 2)
				*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0x6600CC;
			else
				*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0x404040;
		}
		else
			*(unsigned int *)(data->img_p + (j * data->size_line + ra->column_numb * (data->bpp / 8))) = 0x009900;
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
	free(rend_attr);
}