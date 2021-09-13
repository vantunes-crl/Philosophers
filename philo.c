#include "philo.h"

int	is_dead(t_data *data, long old_time, int index)
{
	if (data->meals[index] - old_time > data->time_to_die)
	{
		printf("morreu %d\n", index);
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % 5]);
		return 1;
	}
	return (0);
}

int take_fork_eat(void *arg, t_data *data, int index)
{
	long time_start;
	long old_time;

	pthread_mutex_lock(&data->forks[index]);
	pthread_mutex_lock(&data->forks[(index + 1) % 5]);
	action('e', index);
	time_start = chronometer();
	old_time = data->meals[index];
	data->meals[index] = time_start;
	printf("the last meal of philo %d was %ld \n", index ,data->meals[index] - old_time);
	while (chronometer() - time_start < data->time_to_eat)
	{
		if (is_dead(data, old_time, index))
			return 1;
	}
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % 5]);
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
		if (take_fork_eat(arg, data, index))
			break ;
		usleep(100);
	}
	return (arg);
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
	return (0);
}