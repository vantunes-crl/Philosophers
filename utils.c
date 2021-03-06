/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantunes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:53:06 by vantunes          #+#    #+#             */
/*   Updated: 2021/09/16 13:53:08 by vantunes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data->forks)
		free(data->forks);
	if (data->th_id)
		free(data->th_id);
	return ;
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
	return (((time.tv_sec - start_sec) * 1000)
		+ (time.tv_usec - start_micro_sec) / 1000);
}

void	action(int a, int index, t_data *data)
{
	usleep(100);
	pthread_mutex_lock(&data->action);
	if (a == 'f' && !data->is_dead)
	{
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE GREEN "\thas taken a fork\n" CLOSE, chronometer(), index);
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE GREEN "\thas taken a fork\n" CLOSE, chronometer(), index);
	}
	else if (a == 's' && !data->is_dead)
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE BG "\tis sleeping\n" CLOSE, chronometer(), index);
	else if (a == 'e' && !data->is_dead)
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE PUR "\tis eating\n" CLOSE, chronometer(), index);
	else if (a == 't' && !data->is_dead)
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE T "\tis thinking\n" CLOSE, chronometer(), index);
	else if (a == 'd' && !data->is_dead)
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE OK "\tis satisfied\n" CLOSE, chronometer(), index);
	pthread_mutex_unlock(&data->action);
}
