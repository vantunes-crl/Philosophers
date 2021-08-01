#include "philo.h"

void *routine(void *arg)
{
    printf("working\n");
    usleep(1000000);    
    printf("done\n");
}

void init_data(t_philo *philo, char **argv, int argc)
{
    philo->num_of_philo = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo->num_times_eat = ft_atoi(argv[5]);
    philo->id = malloc(sizeof(pthread_t) * philo->num_of_philo);
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
        pthread_create(&philo.id[i], NULL, &routine, NULL);
    i = -1;
    while (++i < 2)
        pthread_join(philo.id[i], NULL);
    return (0);
}