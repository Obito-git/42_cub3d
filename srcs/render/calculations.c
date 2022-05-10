/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:51 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:38:21 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->side_distance.x = (float)(data->player.pos.x
				- (int)data->player.pos.x) * ray->delta_distance.x;
		ray->step.x = -1;
	}
	else
	{
		ray->side_distance.x = (float)((int)data->player.pos.x + 1
				- data->player.pos.x)*(ray->delta_distance.x);
		ray->step.x = 1;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->side_distance.y = (float)(data->player.pos.y
				- (int)data->player.pos.y) * (ray->delta_distance.y);
		ray->step.y = -1;
	}
	else
	{
		ray->side_distance.y = (float)((int)data->player.pos.y + 1
				- data->player.pos.y)*(ray->delta_distance.y);
		ray->step.y = 1;
	}
}

void	set_side_dist_helper(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_distance.x < ray->side_distance.y)
		{
			ray->side_distance.x += ray->delta_distance.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_distance.y += ray->delta_distance.y;
			ray->map.y += ray->step.y;
			ray->side = 2;
		}
		if (data->world_map[(int)ray->map.x][(int)ray->map.y] == '1')
			ray->hit = true;
	}
	if (ray->side == 0 && ray->ray_dir.x < 0)
		ray->side = 1;
	if (ray->side == 2 && ray->ray_dir.y < 0)
		ray->side = 3;
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = ray->side_distance.x - ray->delta_distance.x;
	else
		ray->perp_wall_dist = ray->side_distance.y - ray->delta_distance.y;
}

void	set_texture_position(t_data *data, t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0 || ray->side == 1)
		ray->wall.x = data->player.pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall.x = data->player.pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	ray->wall.x -= floor(ray->wall.x);
	ray->texture.x = (int)(ray->wall.x * (double) TEXTURE_SIZE);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->texture.x = TEXTURE_SIZE - ray->texture.x - 1;
	if (ray->side == 2 && ray->ray_dir.y < 0)
		ray->texture.x = TEXTURE_SIZE - ray->texture.x - 1;
	ray->texture_step = 1.0 * TEXTURE_SIZE / ray->line_height;
	ray->texture_pos = (ray->draw_start - HEIGHT / 2
			+ ray->line_height / 2) * ray->texture_step;
}

void	set_distance(t_data *data, t_ray *ray)
{
	ray->camera.x = 2 * ray->current_pixel.x / (double) WIDTH - 1;
	set_2point_coord(&ray->ray_dir,
		data->player.dir.x + ray->plane->x * ray->camera.x,
		data->player.dir.y + ray->plane->y * ray->camera.x);
	set_2point_coord(&ray->map,
		(int) data->player.pos.x, (int) data->player.pos.y);
	set_2point_coord(&ray->delta_distance,
		fabs(1 / ray->ray_dir.x), fabs(1 / ray->ray_dir.y));
	set_side_dist(data, ray);
	set_side_dist_helper(data, ray);
}
