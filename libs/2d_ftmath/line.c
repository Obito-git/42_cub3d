/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:25 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 18:26:44 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math2d.h"

void	copy_2line(t_2line *this, t_2line to_copy)
{
	set_2line_point(this, to_copy.point);
	set_2line_dir(this, to_copy.dir);
}

void	set_2line_point(t_2line *this, t_2point new_point)
{
	copy_2point(&(this->point), new_point);
}

void	set_2line_dir(t_2line *this, t_2vector new_dir)
{
	copy_2point(&(this->dir), new_dir);
}

t_2line	create_2line(t_2point point, t_2vector dir)
{
	t_2line	ret;

	set_2line_point(&ret, point);
	set_2line_dir(&ret, dir);
	return (ret);
}
