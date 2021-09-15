#include "philo.h"

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
		usleep(100);
	}
	if (!data->is_dead)
		action('d', index, data);
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
		error("Invalid number of args", &data);
	init_data(&data, argv, argc);
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_mutex_init(&data.forks[i], NULL) != 0)
			error("init thread", &data);
	}
	if (pthread_mutex_init(&data.dead, NULL) != 0)
		error("init thread", &data);
	if (pthread_mutex_init(&data.action, NULL) != 0)
		error("init thread", &data);
	i = -1;
	while (++i < data.num_of_philo)
	{
		content = init_content(&data, i);
		if (pthread_create(&data.th_id[i], NULL, &routine, (void * )content) != 0)
			error("create thread", &data);
	}
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_join(data.th_id[i], NULL) != 0)
			error("join thread", &data);
	}
	i = -1;
	while (++i < data.num_of_philo)
	{
		if (pthread_mutex_destroy(&(data.forks[i])) != 0)
			error("destroy thread", &data);
	}
	if (pthread_mutex_destroy(&(data.dead)) != 0)
		error("destroy thread", &data);
	if (pthread_mutex_destroy(&(data.action)) != 0)
		error("destroy thread", &data);
	return (0);
}