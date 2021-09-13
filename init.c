#include "philo.h"

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
	data->meals = malloc(sizeof(long) * data->num_of_philo);
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