#include "philo.h"

int	is_dead(t_data *data, int index)
{
	pthread_mutex_lock(&data->dead);
	if (chronometer() - data->meals[index] > data->time_to_die
		&& !data->is_dead)
	{
		usleep(500);
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE RED "\tdied..\n" CLOSE, chronometer(), index);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
}

int	start_eat(t_data *data, int index)
{
	long	time_start;

	time_start = 0;
	time_start = chronometer();
	data->meals[index] = time_start;
	usleep(100);
	if (is_dead(data, index))
		return (1);
	if (!data->is_dead)
		action('e', index, data);
	while (chronometer() - time_start < data->time_to_eat && !data->is_dead)
	{
		if (is_dead(data, index))
			return (1);
		usleep(100);
	}
	return (0);
}

int	take_fork(void *arg, t_data *data, int index)
{
	if (data->num_of_philo == 1)
	{
		while (chronometer() < data->time_to_die)
			;
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d" CLOSE RED
			"\tdied..\n" CLOSE, chronometer(), index);
		data->is_dead = 1;
		return (0);
	}
	pthread_mutex_lock(&data->forks[index]);
	pthread_mutex_lock(&data->forks[(index + 1) % data->num_of_philo]);
	if (is_dead(data, index))
		return (1);
	if (!data->is_dead)
		action('f', index, data);
	if (!data->is_dead)
		start_eat(data, index);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
	return (0);
}

int	start_sleep(t_data *data, int index)
{
	long	time_start;

	time_start = chronometer();
	if (is_dead(data, index))
		return (1);
	if (!data->is_dead)
		action('s', index, data);
	while (chronometer() - time_start < data->time_to_sleep)
	{
		if (is_dead(data, index))
			return (1);
		usleep(100);
	}
	return (0);
}
