#ifndef FT_MATH2D_H
# define FT_MATH2D_H

#include <math.h>

typedef	struct	s_2point
{
	double	x;
	double	y;
}				t_2point;

typedef	t_2point t_2vector;

void		copy_2point(t_2point *this, t_2point to_copy);
void		set_2point_coord(t_2point	*this, double x, double y);

void		add_2vector(t_2point *this, t_2point vector);
void		substract_2vector(t_2point *this, t_2point vector);
void		multiply_2vector(t_2point *this, double);
void		normalise_2vector(t_2point *this);

t_2point	vector2_sum(t_2point this, t_2point vector);
t_2point	vector2_sub(t_2point this, t_2point vector);
t_2point	vector2_mult(t_2point this, double nbr);
t_2point	vector2_normalized(t_2point this);
float		v2d_lenght(t_2vector a);

t_2point	create_2point(double x, double y);

typedef struct s_2line
{
    t_2point   point;
    t_2vector  dir;
}               t_2line;

void		copy_2line(t_2line *this, t_2line to_copy);
void		set_2line_point(t_2line *this, t_2point new_point);
void		set_2line_dir(t_2line *this, t_2vector new_dir);

t_2point	get_2line_point(t_2line this);
t_2vector	get_2line_dir(t_2line this);

t_2point	*get_2line_pointp(t_2line *this);
t_2vector	*get_2line_dirp(t_2line *this);

t_2line			create_2line(t_2point point, t_2vector dir);

typedef t_2line t_2ray;


typedef	struct s_2segment
{
	t_2point	a;
	t_2point	b;
}				t_2segment;

void		set_2segment_a(t_2segment	*this, t_2point a);
void		set_2segment_b(t_2segment	*this, t_2point b);
void		set_2segment_pts(t_2segment	*this, t_2point x, t_2point y);

t_2point	get_2segment_a(t_2segment this);
t_2point	get_2segment_b(t_2segment this);
double		get_2segment_l(t_2segment this);

t_2point	*get_2segment_ap(t_2segment *this);
t_2point	*get_2segment_bp(t_2segment *this);

t_2segment		create_2segment(t_2point a, t_2point b);

#endif