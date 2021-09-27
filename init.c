/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantunes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:52:31 by vantunes          #+#    #+#             */
/*   Updated: 2021/09/16 13:52:34 by vantunes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_caracters(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(1, "Error\n", 6);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (check_caracters(argv))
		return (-1);
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_times_eat = -1;
	if (data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
	{
		printf("can't be zero\n");
		return (-1);
	}
	if (argc == 6)
		data->num_times_eat = ft_atoi(argv[5]);
	data->th_id = malloc(sizeof(pthread_t) * data->num_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->is_dead = 0;
	return (0);
}

t_content	*init_content(t_data *data, int index)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->data = data;
	content->philo_id = index + 1;
	content->last_meal = 0;
	return (content);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			error("init thread", data);
	}
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		error("init thread", data);
	if (pthread_mutex_init(&data->action, NULL) != 0)
		error("init thread", data);
}
