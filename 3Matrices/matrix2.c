#include "../Includes/minirt.h"

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
	int		x;
	int		y;
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
