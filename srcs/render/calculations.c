#include "cub3d.h"

void	set_side_dist(t_data *data) 
{
	if (data->ray_dir.x < 0)
	{
		data->side_distance.x = (float)(data->player.pos.x -
			(int)data->player.pos.x) * data->delta_distance.x;
		data->step.x = -1;
	}
	else
	{
		data->side_distance.x = (float)((int)data->player.pos.x + 1 -
			data->player.pos.x) * data->delta_distance.x;
		data->step.x = 1;
	}
	if (data->ray_dir.y < 0)
	{
		data->side_distance.y = (float)(data->player.pos.y -
			(int)data->player.pos.y) * data->delta_distance.y;
		data->step.y = -1;
	}
	else
	{
		data->side_distance.y = (float)((int)data->player.pos.y + 1 -
			data->player.pos.y) * data->delta_distance.y;
		data->step.y = 1;
	}
}

void	set_side_dist_helper(t_data *data)
{
	while (!data->hit)
	{
		if (data->side_distance.x < data->side_distance.y)
		{
			data->side_distance.x += data->delta_distance.x;
			data->map.x += data->step.x;
			data->side = 0;
		}
		else
		{
			data->side_distance.y += data->delta_distance.y;
			data->map.y += data->step.y;
			data->side = 2;
		}
		if (data->world_map[(int)data->map.x][(int)data->map.y] == '1')
			data->hit = true;
	}
	if (data->side == 0 && data->ray_dir.x < 0)
		data->side = 1;
	if (data->side == 2 && data->ray_dir.y < 0)
		data->side = 3;
	if (data->side == 0)
		data->perpWallDist = data->side_distance.x - data->delta_distance.x;
	else
		data->perpWallDist = data->side_distance.y - data->delta_distance.y;
}

void	set_distance(t_data *data, int x)
{
	data->camera.x = 2 * x / (double) WIDTH - 1;
	set_2point_coord(&data->ray_dir,
		data->player.dir.x + data->plane->x * data->camera.x,
		data->player.dir.y + data->plane->y * data->camera.x);
	set_2point_coord(&data->map,
		(int) data->player.pos.x, (int) data->player.pos.y);
	set_2point_coord(&data->delta_distance, fabs(1 / data->ray_dir.x), fabs(1 / data->ray_dir.y));
	set_side_dist(data);
	set_side_dist_helper(data);
}