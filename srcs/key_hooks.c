/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:45 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:44:34 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_handler(int x, int y, void *param)
{
	t_data	*data;

	(void) y;
	data = (t_data *) param;
	if (x > WIDTH / 2 - 400 && x < WIDTH / 2 + 400)
		return (0);
	if (x < WIDTH / 2 - 400)
	{
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
		turn(ARW_L, data);
	}
	else if (x > WIDTH / 2 + 400)
	{
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
		turn(ARW_R, data);
	}
	return (0);
}

void	move(int keycode, t_data *data)
{
	t_2vector	new;
	float		s;

	s = 0.3;
	if (keycode == W)
		new = vector2_sum(data->player.pos, vector2_mult(data->player.dir, s));
	else if (keycode == A)
		new = vector2_sub(data->player.pos, vector2_mult(data->player.cam, s));
	else if (keycode == S)
		new = vector2_sub(data->player.pos, vector2_mult(data->player.dir, s));
	else if (keycode == D)
		new = vector2_sum(data->player.pos, vector2_mult(data->player.cam, s));
	if (data->world_map[(int)new.x][(int)new.y] == '1')
		return ;
	if ((((int)data->player.pos.x != (int)new.x)
			|| ((int)data->player.pos.y != (int)new.y))
		&& (data->world_map[(int)new.x][(int)new.y] != '1'))
	{
		data->world_map[(int)data->player.pos.x][(int)data->player.pos.y] = '0';
		data->world_map[(int)new.x][(int)new.y] = 'P';
	}
	if (data->world_map[(int)new.x][(int)new.y] != '1')
		data->player.pos = new;
	render(data);
}

void	turn(int keycode, t_data *data)
{
	t_2vector	old_dir;
	t_2vector	old_cam;
	t_player	*p;
	int			s;

	s = 349;
	p = &data->player;
	old_dir = data->player.dir;
	old_cam = data->player.cam;
	if (keycode == ARW_L)
	{
		p->dir.x = old_dir.x * cos(-sqrt(s)) - old_dir.y * sin(-sqrt(s));
		p->dir.y = old_dir.x * sin(-sqrt(s)) + old_dir.y * cos(-sqrt(s));
		p->cam.x = old_cam.x * cos(-sqrt(s)) - old_dir.y * sin(-sqrt(s));
		p->cam.y = old_cam.x * sin(-sqrt(s)) + old_dir.y * cos(-sqrt(s));
	}
	if (keycode == ARW_R)
	{
		p->dir.x = old_dir.x * cos(sqrt(s)) - old_dir.y * sin(sqrt(s));
		p->dir.y = old_dir.x * sin(sqrt(s)) + old_dir.y * cos(sqrt(s));
		p->cam.x = old_cam.x * cos(sqrt(s)) - old_dir.y * sin(sqrt(s));
		p->cam.y = old_cam.x * sin(sqrt(s)) + old_dir.y * cos(sqrt(s));
	}
	set_cam_vector(data);
	render(data);
}

int	key_hooks(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_exit(data);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		move(keycode, data);
	else if (keycode == ARW_L || keycode == ARW_R)
		turn(keycode, data);
	return (0);
}
