#include "2d_ftmath.h"

void		add_2vector(t_2point *this, t_2point vector)
{
	this->x += vector.x;
	this->y += vector.y;
}

void		substract_2vector(t_2point *this, t_2point vector)
{
	this->x -= vector.x;
	this->y += vector.y;
}

void		multiply_2vector(t_2point *this, double nbr)
{
	this->x *= nbr;
	this->y *= nbr;
}

void		normalise_2vector(t_2point *this)
{
	(void)this;
}


t_2point	vector2_sum(t_2point this,t_2point vector)
{
	t_2point	ret;

	ret.x = this.x + vector.x;
	ret.y = this.y + vector.y;
	return (ret);
}

t_2point	vector2_sub(t_2point this,t_2point vector)
{
	t_2point	ret;

	ret.x = this.x - vector.x;
	ret.y = this.y - vector.y;
	return (ret);
}

t_2point	vector2_mult(t_2point this, double nbr)
{
	t_2point	ret;

	ret.x = this.x * nbr;
	ret.y = this.y * nbr;
	return (ret);
}

t_2point	vector2_normalized(t_2point this)
{
	t_2point	ret;

	copy_2point(&ret, this);
	return (ret);
}