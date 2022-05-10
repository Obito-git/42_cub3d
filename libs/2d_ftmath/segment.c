/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:45:23 by lnelson           #+#    #+#             */
/*   Updated: 2022/05/10 18:26:46 by lnelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math2d.h"

void	set_2segment_a(t_2segment	*this, t_2point a)
{
	copy_2point(&(this->a), a);
}

void	set_2segment_b(t_2segment	*this, t_2point b)
{
	copy_2point(&(this->b), b);
}

void	set_2segment_pts(t_2segment	*this, t_2point a, t_2point b)
{
	set_2segment_a(this, a);
	set_2segment_b(this, b);
}

double	get_2segment_l(t_2segment this)
{
	t_2point	temp;

	temp.x = this.a.x - this.b.x;
	temp.y = this.a.y - this.b.y;
	return (sqrt(pow(temp.x, 2) + pow(temp.y, 2)));
}

t_2segment	create_2segment(t_2point a, t_2point b)
{
	t_2segment	ret;

	set_2segment_pts(&ret, a, b);
	return (ret);
}
