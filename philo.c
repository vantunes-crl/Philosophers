#include "philo.h"

int	is_dead(t_data *data, int index)
{
	pthread_mutex_lock(&data->dead);
	if (chronometer() - data->meals[index] > data->time_to_die && !data->is_dead)
	{
		usleep(100);
		printf(BLUE "%ld" CLOSE YELL "\tPhilo %d" CLOSE RED "\tdied..\n" CLOSE, chronometer(), index);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
		pthread_mutex_unlock(&data->dead);
		return 1;
	}
	else
	{
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
}

int start_eat(t_data *data, int index)
{
	long time_start = 0;

	time_start = chronometer();
	data->meals[index] = time_start;
	if (is_dead(data, index))
		return 1;
	if(!data->is_dead)
		action('e', index, data);
	while (chronometer() - time_start < data->time_to_eat)
	{
		if (is_dead(data, index))
			return (1);
	}
	return (0);
}

int take_fork(void *arg, t_data *data, int index)
{
	pthread_mutex_lock(&data->forks[index]);
	pthread_mutex_lock(&data->forks[(index + 1) % data->num_of_philo]);
	if (is_dead(data, index))
		return 1;
	if(!data->is_dead)
		action('f', index, data);
	if (!data->is_dead)
		start_eat(data, index);
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
	return (0);
}

int start_sleep(t_data *data, int index)
{
	long time_start;

	time_start = chronometer();
	if (is_dead(data, index))
		return 1;
	if(!data->is_dead)
		action('s', index, data);
	while (chronometer() - time_start < data->time_to_sleep)
	{
		if (is_dead(data, index))
			return 1;
	}
	return (0);
}

void *routine(void *arg)
{
	t_data *data;
	int index;
	int  times_to_eat;
	data = ((t_content *)arg)->data;
	index = ((t_content *)arg)->philo_id;
	times_to_eat = data->num_times_eat;
	while (times_to_eat--)
	{   
		if (data->is_dead)
			break ;
		if (take_fork(arg, data, index))
			break ;
		if (start_sleep(data, index))
			break ;
		if (is_dead(data, index))
			break ;
		if(!data->is_dead)
			action('t', index, data);
	}
	free(arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data      data;
	t_content *content;
	int i;

	memset(&data, 0, sizeof(data));
	if (argc != 5 && argc != 6)
		error("Invalid number of args");
	init_data(&data, argv, argc);
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_init(&data.forks[i], NULL);
	pthread_mutex_init(&data.dead, NULL);
	i = -1;
	while (++i < data.num_of_philo)
	{
		content = init_content(&data, i);
		if (pthread_create(&data.th_id[i], NULL, &routine, (void * )content) != 0)
			error("create thread");
	}
	i = -1;
	while (++i < data.num_of_philo)
		pthread_join(data.th_id[i], NULL);
	i = -1;
	while (++i < data.num_of_philo)
		pthread_mutex_destroy(&(data.forks[i]));
	pthread_mutex_destroy(&(data.dead));
	free(data.meals);
	free(data.forks);
	free(data.th_id);
	return (0);
}