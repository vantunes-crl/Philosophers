/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantunes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:52:58 by vantunes          #+#    #+#             */
/*   Updated: 2021/09/16 13:53:00 by vantunes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELL "\033[1;33m"
# define BLUE "\033[1;34m"
# define PUR "\033[1;35m"
# define BG "\033[1;36m"
# define T "\033[1;37m"
# define CLOSE "\033[0m"
# define OK "\033[0;36m"

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_eat;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead;
	pthread_mutex_t	action;
	pthread_t		*th_id;

}				t_data;

typedef struct s_content
{
	t_data	*data;
	int		philo_id;
	long	last_meal;
}				t_content;

/* utils */
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		error(char *str, t_data *data);
long		chronometer(void);

/* inits */
int			init_data(t_data *data, char **argv, int argc);
t_content	*init_content(t_data *data, int index);
void		mutex_init(t_data *data);

/* actions */
void		action(int a, int index, t_data *data);
int			start_sleep(void *content, t_data *data, int index);
int			is_dead(void *content);
int			death_handler(t_data *data, int index);
int			start_eat(void *content, t_data *data, int index);
int			take_fork(void *content, t_data *data, int index);

#endif
