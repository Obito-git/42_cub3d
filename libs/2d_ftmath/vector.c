/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:19 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 17:47:43 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "2d_ftmath.h"

void	add_2vector(t_2point *this, t_2point vector)
{
	this->x += vector.x;
	this->y += vector.y;
}

void	substract_2vector(t_2point *this, t_2point vector)
{
	this->x -= vector.x;
	this->y += vector.y;
}

t_2point	vector2_sum(t_2point this, t_2point vector)
{
	t_2point	ret;

	ret.x = this.x + vector.x;
	ret.y = this.y + vector.y;
	return (ret);
}

t_2point	vector2_sub(t_2point this, t_2point vector)
{
	t_2point	ret;

	ret.x = this.x - vector.x;
	ret.y = this.y - vector.y;
	return (ret);
}

float	v2d_lenght(t_2vector a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2)));
}
