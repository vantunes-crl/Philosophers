#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_data
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_eat;
    long *meals;
    pthread_mutex_t *forks;
    pthread_t       *th_id;

}              t_data;

typedef struct s_content
{
    t_data  *data;
    int     philo_id;
    long    last_meal;
}              t_content;

void	ft_bzero(void *s, size_t n);
int     ft_atoi(const char *str);
void    error(char *str);
long	chronometer(void);
void    init_data(t_data *data, char **argv, int argc);
t_content *init_content(t_data *data, int index);
void action(int a, int index);

#endif