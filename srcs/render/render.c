/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:18:58 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:19:19 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_side_texture(t_data *data, t_ray *ray)
{
	if (ray->side == NORTH_T)
		return (&data->texture.north);
	if (ray->side == EAST_T)
		return (&data->texture.east);
	if (ray->side == SOUTH_T)
		return (&data->texture.south);
	(void) ray;
	return (&data->texture.west);
}

void	draw_texture(t_data *data, t_ray *ray, t_image *texture)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		*(unsigned int *)(data->img.addr + ((int)ray->current_pixel.y
					* data->img.size_line
					+ (int)ray->current_pixel.x * (data->img.bpp / 8) + i))
			= (unsigned int)(texture->addr[(int)ray->texture.y
				* data->texture.north.size_line + (int)ray->texture.x
				* (data->texture.north.bpp / 8) + i]);
		i++;
	}
}

void	refresh_variables(t_ray *ray, t_image *texture)
{
	int		tmp;

	tmp = (int)ray->current_pixel.y * texture->size_line - HEIGHT
		* texture->size_line / 2 + ray->line_height * texture->size_line / 2;
	ray->texture.y = (int)(((tmp * TEXTURE_SIZE)
				/ ray->line_height) / texture->size_line);
	ray->texture_pos += ray->texture_step;
}

void	render_collum(t_data *data, t_ray *ray)
{
	t_image	*texture;

	set_distance(data, ray);
	set_texture_position(data, ray);
	while ((int)ray->current_pixel.y <= HEIGHT)
	{
		texture = get_side_texture(data, ray);
		refresh_variables(ray, texture);
		if (ray->current_pixel.y < ray->draw_start)
			*(unsigned int *)(data->img.addr + ((int)ray->current_pixel.y
						* data->img.size_line + (int)ray->current_pixel.x
						* (data->img.bpp / 8))) = data->img.sky_color;
		else if (ray->current_pixel.y >= ray->draw_start
			&& ray->current_pixel.y <= ray->draw_end)
			draw_texture(data, ray, texture);
		else
			*(unsigned int *)(data->img.addr + ((int)ray->current_pixel.y
						* data->img.size_line + (int)ray->current_pixel.x
						* (data->img.bpp / 8))) = data->img.floor_color;
		ray->current_pixel.y += 1;
	}
}

void	render(t_data *data)
{
	t_ray	ray;

	ray.current_pixel.x = 0;
	ray.plane = &data->player.cam;
	while (ray.current_pixel.x < WIDTH)
	{
		ray.current_pixel.y = 0;
		ray.hit = false;
		render_collum(data, &ray);
		ray.current_pixel.x++;
	}
	ray.current_pixel.x = 0;
	while ((int)ray.current_pixel.x < HEIGHT)
	{
		*(unsigned int *)(data->img.addr + ((int)ray.current_pixel.x
					* data->img.size_line + 0)) = 0;
		ray.current_pixel.x += 1;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	render_minimap(data);
}
