#include "Includes/minirt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 0, 3, x);
	set_index(&matrix, 1, 3, y);
	set_index(&matrix, 2, 3, z);
	return (matrix);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 0, 0, x);
	set_index(&matrix, 1, 1, y);
	set_index(&matrix, 2, 2, z);
	return (matrix);
}

t_matrix	shearing(double *x, double *y, double *z)
{
	t_matrix	matrix;

	matrix = identity();
	set_index(&matrix, 0, 1, x[0]);
	set_index(&matrix, 0, 2, x[1]);
	set_index(&matrix, 1, 0, y[0]);
	set_index(&matrix, 1, 2, y[1]);
	set_index(&matrix, 2, 0, z[0]);
	set_index(&matrix, 2, 1, z[1]);
	return (matrix);
}
