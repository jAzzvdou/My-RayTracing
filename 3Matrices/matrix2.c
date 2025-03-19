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
