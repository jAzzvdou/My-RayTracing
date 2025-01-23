#include "../Includes/minirt.h"

char	*my_strdup(const char *s)
{
	int		i;
	char	*final;

	final = memcard(NULL, STRING, MALLOC, my_strlen(s));
	if (!final)
		return (NULL);
	i = -1;
	while (s[++i])
		final[i] = s[i];
	final[i] = '\0';
	return (final);
}

static size_t	house_places(int n)
{
	size_t	places;

	places = 0;
	if (n < 0)
		places++;
	while (n != 0)
	{
		n /= 10;
		places++;
	}
	return (places);
}

char	*my_itoa(int n)
{
	size_t	size_n;
	char	*new_s;

	if (n == -2147483648)
		return (my_strdup("-2147483648"));
	if (n == 0)
		return (my_strdup("0"));
	size_n = house_places(n);
	new_s = memcard(NULL, STRING, MALLOC, size_n);
	if (!new_s)
		return (NULL);
	new_s[size_n--] = '\0';
	if (n < 0)
	{
		new_s[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		new_s[size_n--] = n % 10 + '0';
		n /= 10;
	}
	return (new_s);
}
