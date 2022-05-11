/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:06:42 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:43:06 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	starter(int ac, char **av, t_data *data)
{
	int	fd;

	if (ac != 2)
		return (ret_error("cub3d: Error, must have 1 argument.\n", 2));
	if (check_file_name(av[1]) == 0)
		return (ret_error("cube3d: Error, file must be a <.cub> type.\n", 2));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ret_error("cub3d: Error, unable to open file.\n", 2));
	init_data(data);
	parsing(data, fd);
	close(fd);
	if (map_processing(data) < 0 || !check_player_count(data->world_map))
	{
		ft_putstr_fd("cub3d: Error, file corrupted\n", 2);
		ft_exit(data);
	}
	data->mlx = mlx_init();
	if (get_textures(data) == 0)
	{
		ft_putstr_fd("cub3d: Error, unable to acces textures.\n", 2);
		ft_exit(data);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (starter(ac, av, &data) != 0)
		return (2);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.size_line, &data.img.endian);
	render(&data);
	mlx_hook(data.win, 06, 1L << 6, mouse_handler, &data);
	mlx_hook(data.win, 2, 1L << 0, key_hooks, &data);
	mlx_hook(data.win, 17, 1L << 2, ft_exit, &data);
	mlx_loop(data.mlx);
	ft_exit(&data);
	return (0);
}
