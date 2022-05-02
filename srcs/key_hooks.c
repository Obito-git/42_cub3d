#include "cub3d.h"

void	move(int keycode, t_data *data)
{
	t_vector_2d new;
	float		s;

	s = 0.3;
	if (keycode == W)
		new = add_vectors(data->player.pos, scalar_mult(data->player.dir, s));
	else if (keycode == A)
		new = sub_vectors(data->player.pos, scalar_mult(data->player.cam, s));
	else if (keycode == S)
		new = sub_vectors(data->player.pos, scalar_mult(data->player.dir, s));
	else if (keycode == D)
		new = add_vectors(data->player.pos, scalar_mult(data->player.cam, s));
	if (data->map[(int)new.x][(int)new.y] != '1')
		data->player.pos = new;
}

void	turn(int keycode, t_data *data)
{
	t_vector_2d old_dir;
	t_vector_2d old_cam;
	int			s;

	s = 345;
	old_dir = data->player.dir;
	old_cam = data->player.cam;
	if (keycode == ARW_L)
	{
		data->player.dir.x = old_dir.x * cos(-sqrt(s)) - old_dir.y * sin(-sqrt(s));
		data->player.dir.y = old_dir.x * sin(-sqrt(s)) + old_dir.y * cos(-sqrt(s));
		data->player.cam.x = old_cam.x * cos(-sqrt(s)) - old_dir.y * sin(-sqrt(s));
		data->player.cam.y = old_cam.x * sin(-sqrt(s)) + old_dir.y * cos(-sqrt(s));
	}
	if (keycode == ARW_R)
	{
		data->player.dir.x = old_dir.x * cos(sqrt(s)) - old_dir.y * sin(sqrt(s));
		data->player.dir.y = old_dir.x * sin(sqrt(s)) + old_dir.y * cos(sqrt(s));
		data->player.cam.x = old_cam.x * cos(sqrt(s)) - old_dir.y * sin(sqrt(s));
		data->player.cam.y = old_cam.x * sin(sqrt(s)) + old_dir.y * cos(sqrt(s));
	}
	printf("player dir = [ %f : %f ] | lenght = %f \n", data->player.dir.x, data->player.dir.y, v2d_lenght(data->player.dir));
	set_cam_vector(data);
}

int	key_hooks(int keycode, t_data *data)
{
	if (keycode == ESC)
		ft_exit(data);
	if (keycode == W || keycode == A || keycode == S || keycode == D
		|| keycode == ARW_L || keycode == ARW_R)
	{
		if (keycode == W || keycode == A || keycode == S || keycode == D)
			move(keycode, data);
		else
			turn(keycode, data);
		render(data);
	}
	return (0);
}