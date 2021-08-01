#include "philo.h"

void error(char *str)
{
    printf("%s\n", str);
    exit(1);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	n;

	i = 0;
	neg = 1;
	n = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n * neg);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}