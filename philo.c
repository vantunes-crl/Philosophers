#include "philo.h"

void *eating(t_data *data)
{
    long		t_start;

	t_start = timer();

    while (timer() - t_start < data->time_to_eat)
    {
        usleep(100);
    }
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
        printf ("Philosopher %d is thinking\n", index);
        pthread_mutex_lock(&data->forks[index]);
        pthread_mutex_lock(&data->forks[(index + 1) % 5]);
        printf ("Philosopher %d is eating\n",index);
        pthread_mutex_unlock(&data->forks[index]);
        pthread_mutex_unlock(&data->forks[(index + 1) % 5]);
        printf ("Philosopher %d finished eating\n", index);
    }
    return (arg);
}

void init_data(t_data *data, char **argv, int argc)
{
    data->num_of_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->num_times_eat = -1;
    if (argc == 6)
        data->num_times_eat = ft_atoi(argv[5]);
    data->th_id = malloc(sizeof(pthread_t) * data->num_of_philo);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
}

t_content *init_content(t_data *data, int index)
{
    t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->data = data;
	content->philo_id = index;
	return (content);
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