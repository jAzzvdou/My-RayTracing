#include "../Includes/minirt.h"

void	set_index(t_matrix *a, int x, int y, double value)
{
	if (x < 0 || x >= a->cols || y < 0 || y >= a->rows)
		return ;
	a->matrix[y * a->cols + x] = value;
}

double	get_index(t_matrix *a, int x, int y)
{
	if (x < 0 || x >= a->cols || y < 0 || y >= a->rows)
		return (0);
	return (a->matrix[y * a->cols + x]);
}

static double	mult_index(t_matrix a, t_matrix b, int x, int y)
{
	int	i;
	double	result;

	result = 0;
	i = 0;
	while (i < a.cols)
	{
		result += get_index(&a, i, y) * get_index(&b, x, i);
		i++;
	}
	return (result);
}

t_matrix	mult_matrix(t_matrix a, t_matrix b)
{
	int		x;
	int		y;
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	if (a.rows != b.rows || a.cols != b.cols)
		return (matrix);
	matrix.rows = a.rows;
	matrix.cols = a.cols;
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			set_index(&matrix, x, y, mult_index(a, b, x, y));
			x++;
		}
		y++;
	}
	return (matrix);
}

t_tuple	mult_matrix_tuple(t_matrix a, t_tuple b)
{
	t_tuple	result;

	result.x = get_index(&a, 0, 0) * b.x + get_index(&a, 1, 0) * b.y;
	result.x += get_index(&a, 2, 0) * b.z + get_index(&a, 3, 0) * b.w;
	result.y = get_index(&a, 0, 1) * b.x + get_index(&a, 1, 1) * b.y;
	result.y += get_index(&a, 2, 1) * b.z + get_index(&a, 3, 1) * b.w;
	result.z = get_index(&a, 0, 2) * b.x + get_index(&a, 1, 2) * b.y;
	result.z += get_index(&a, 2, 2) * b.z + get_index(&a, 3, 2) * b.w;
	result.w = get_index(&a, 0, 3) * b.x + get_index(&a, 1, 3) * b.y;
	result.w += get_index(&a, 2, 3) * b.z + get_index(&a, 3, 3) * b.w;
	return (result);
}

t_matrix	identity(void)
{
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	matrix.rows = 4;
	matrix.cols = 4;
	set_index(&matrix, 0, 0, 1);
	set_index(&matrix, 1, 1, 1);
	set_index(&matrix, 2, 2, 1);
	set_index(&matrix, 3, 3, 1);
	return (matrix);
}

t_matrix	transpose(t_matrix a)
{
	int			x;
	int			y;
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	matrix.rows = a.cols;
	matrix.cols = a.rows;
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			set_index(&matrix, x, y, get_index(&a, y, x));
			x++;
		}
		y++;
	}
	return (matrix);
}

t_matrix	submatrix(t_matrix a, int x, int y)
{
	int		x1[2];
	int		y1[2];
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	matrix.rows = a.rows - 1;
	matrix.cols = a.cols - 1;
	y1[0] = -1;
	y1[1] = 0;
	while (++y1[0] < a.rows)
	{
		if (y1[0] == y)
			continue ;
		x1[0] = -1;
		x1[1] = 0;
		while (++x1[0] < a.cols)
		{
			if (x1[0] == x)
				continue ;
			set_index(&matrix, x1[1], y1[1], get_index(&a, x1[0], y1[0]));
			x1[1]++;
		}
		y1[1]++;
	}
	return (matrix);
}

double	minor(t_matrix a, int x, int y)
{
	return (determinant(submatrix(a, x, y)));
}

double	cofactor(t_matrix a, int x, int y)
{
	double		submatrix;

	submatrix = minor(a, x, y);
	if ((x + y) % 2 == 0)
		return (submatrix);
	return (-submatrix);
}

t_matrix	inverse(t_matrix a)
{
	int		x;
	int		y;
	double		det;
	t_matrix	matrix;

	my_bzero(&matrix, sizeof(t_matrix));
	matrix.rows = a.rows;
	matrix.cols = a.cols;
	det = determinant(a);
	if (det == 0)
		return (identity());
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			set_index(&matrix, y, x, cofactor(a, x, y) / det);
			x++;
		}
		y++;
	}
	return (matrix);
}

double	determinant(t_matrix a)
{
	double		result;
	int			i;

	if (a.rows == 2 && a.cols == 2)
	{
		result = get_index(&a, 0, 0) * get_index(&a, 1, 1)
			- get_index(&a, 0, 1) * get_index(&a, 1, 0); 
		return (result);
	}
	result = 0;
	i = 0;
	while (i < a.cols)
	{
		result += get_index(&a, i, 0) * cofactor(a, i, 0);
		i++;
	}
	return (result);
}
