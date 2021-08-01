#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    printf ("Philosopher %d is thinking\n", philo->philo_id);
    pthread_mutex_lock(&philo->forks[philo->philo_id]);
    pthread_mutex_lock(&philo->forks[(philo->philo_id + 1) % 5]);
    printf ("Philosopher %d is eating\n",philo->philo_id);
    sleep(1);
    pthread_mutex_unlock(&philo->forks[philo->philo_id]);
    pthread_mutex_unlock(&philo->forks[(philo->philo_id + 1) % 5]);
    printf ("Philosopher %d finished eating\n",philo->philo_id);
}

void init_data(t_philo *philo, char **argv, int argc)
{
    philo->num_of_philo = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo->num_times_eat = ft_atoi(argv[5]);
    philo->th_id = malloc(sizeof(pthread_t) * philo->num_of_philo);
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philo);
}

int main(int argc, char **argv)
{
    t_philo philo;
    int i;

    memset(&philo, 0, sizeof(philo));
    if (argc != 5 && argc != 6)
        error("Invalid number of args");
    init_data(&philo, argv, argc);
    i = -1;
    while (++i < philo.num_of_philo)
        pthread_mutex_init(&philo.forks[i], NULL);
    philo.philo_id = -1;
    while (++philo.philo_id < philo.num_of_philo)
    {
        if (pthread_create(&philo.th_id[philo.philo_id], NULL, &routine, (void * ) &philo) != 0)
            error("create thread");
    }
    i = -1;
    while (++i < philo.num_of_philo)
        pthread_join(philo.th_id[i], NULL);
    return (0);
}