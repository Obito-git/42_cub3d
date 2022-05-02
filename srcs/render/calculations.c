#include "cub3d.h"

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

void	set_side_dist_helper(t_rend_attr *ra, t_data *data)
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
		ra->deltaDistX = fabs(1 / ra->vector.x);
	//ra->deltaDistX = sqrtf(1 + (powf(ra->vector.y,2) / powf(ra->vector.x, 2)));
	if (ra->vector.y == 0)
		ra->deltaDistY = __FLT_MAX__;
	else
		ra->deltaDistY =  fabs(1 / ra->vector.y);
	//ra->deltaDistY = sqrtf(1 + (powf(ra->vector.x,2) / powf(ra->vector.y, 2)));
	ra->currentX = (int)data->player.pos.x;
	ra->currentY = (int)data->player.pos.y;
	set_side_dist(ra, data);
	set_side_dist_helper(ra, data);
}