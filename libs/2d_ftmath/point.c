/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:24 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:49:31 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2d_ftmath.h"

void	copy_2point(t_2point *this, t_2point to_copy)
{
	this->x = to_copy.x;
	this->y = to_copy.y;
}

void	set_2point_coord(t_2point *this, double x, double y)
{
	this->x = x;
	this->y = y;
}

t_2point	create_2point(double x, double y)
{
	t_2point	res;

	set_2point_coord(&res, x, y);
	return (res);
}
