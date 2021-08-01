#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct s_philo
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_eat;
    pthread_t   *id;

}              t_philo;

void	ft_bzero(void *s, size_t n);
int     ft_atoi(const char *str);
void    error(char *str);

#endif