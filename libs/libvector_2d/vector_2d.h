#ifndef VECTOR_2D_H
# define VECTOR_2D_H

#include "math.h"

typedef	struct	s_vector_2d
{
	float	x;
	float	y;
}				t_vector_2d;

t_vector_2d	add_vectors(t_vector_2d a, t_vector_2d b);
t_vector_2d sub_vectors(t_vector_2d a, t_vector_2d b);

t_vector_2d scalar_mult(t_vector_2d a, float f);

float		v2d_lenght(t_vector_2d a);

#endif