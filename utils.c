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

long	chronometer(void)
{
	struct timeval		time;
	static time_t		start_sec = 0;
	static suseconds_t	start_micro_sec = 0;

	gettimeofday(&time, NULL);
	if (!start_sec)
	{
		start_sec = time.tv_sec;
		start_micro_sec = time.tv_usec;
	}
	return (((time.tv_sec - start_sec) * 1000) + (time.tv_usec - start_micro_sec) / 1000);
}

void action(int a, int index)
{
	if (a == 'f')
	{
		printf("\033[0;32m%ld\033[0m\t\033[0;34mPhilo %d\033[0m\t\033[1;31mtake the fork\n", chronometer(), index);
		printf("\033[0;32m%ld\033[0m\t\033[0;34mPhilo %d\033[0m\t\033[1;31mtake the fork\n", chronometer(), index);
	}
	else if (a == 's')
		printf("\033[0;33m%ld\033[0m\t\033[0;34mPhilo %d\033[0m\t\033[1;35mstart sleep\n", chronometer(), index);
	else if (a == 'e')
		printf("\033[0;32m%ld\033[0m\t\033[0;34mPhilo %d\033[0m\t\033[1;37mis eating\n", chronometer(), index);
	else if (a == 't')
		printf("\033[0;32m%ld\033[0m\t\033[0;34mPhilo %d\033[0m\t\033[1;36mis thinking\n", chronometer(), index);
}