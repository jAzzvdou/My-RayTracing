#include "../Includes/minirt.h"

int	get_line_token(char *line)
{
	char *token;

	if (!line)
		return (-1);
	else if (ft_strcmp(line, "A ", 2) == 0)
		return (A);
	else if (ft_strcmp(line, "C ", 2) == 0)
		return (C);
	else if (ft_strcmp(line, "L ", 2) == 0)
		return (L);
	else if (ft_strcmp(line, "sp ", 3) == 0)
		return (SP);
	else if (ft_strcmp(line, "pl ", 3) == 0)
		return (PL);
	else if (ft_strcmp(line, "cy", 3) == 0)
		return (CY);
	else if (ft_strcmp(line, "cn ", 3) == 0)
		return (CN);
	else if (ft_strcmp(line, "P ", 2) == 0)
		return (P);
	else if (ft_strcmp(line, "m ", 2) == 0)
		return (MT);
	return (-1);
}

int	parse_line(char *line, t_world *w)
{
	int	token;

	token = get_line_token(line);

	return (1);
}

int	parse(int fd, t_world *w)
{
	int		line_count;
	char	*line;

	line_count = 1;
	*w = default_world();
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!parse_line(line, w))
		{
			printf("line error -> %i", line_count);
			return (0);
		}
		printf("line %i -> %s\n", line_count, line);
		free(line);
		line = get_next_line(fd);
		line_count++;
	}
	return (1);
}
