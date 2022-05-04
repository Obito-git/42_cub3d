#include "vector_2d.h"
t_vector_2d	create_vector(float x, float y)
{
	t_vector_2d	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_vector_2d add_vectors(t_vector_2d a, t_vector_2d b)
{
	t_vector_2d c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return (c);
}

t_vector_2d sub_vectors(t_vector_2d a, t_vector_2d b)
{
	t_vector_2d c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return (c);
}

t_vector_2d scalar_mult(t_vector_2d a, float f)
{
	t_vector_2d c;

	c.x = a.x * f;
	c.y = a.y * f;
	return (c);
}

float		v2d_lenght(t_vector_2d a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2)));
}