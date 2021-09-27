/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantunes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:52:21 by vantunes          #+#    #+#             */
/*   Updated: 2021/09/16 13:52:24 by vantunes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(void *content)
{
	t_data		*data;
	long		last_meal;

	data = ((t_content *)content)->data;
	last_meal = ((t_content *)content)->last_meal;
	if (chronometer() - last_meal >= data->time_to_die)
		return (1);
	return (0);
}

int	death_handler(t_data *data, int index)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead)
	{
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
		pthread_mutex_unlock(&data->dead);
		return (0);
	}
	else
	{
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d"
			CLOSE RED "\tdied\n" CLOSE, (long)data->time_to_die + 1, index);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->forks[index]);
		pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
}

int	start_eat(void *content, t_data *data, int index)
{
	long	time_start;

	time_start = chronometer();
	((t_content *)content)->last_meal = time_start;
	action('e', index, data);
	while (chronometer() - time_start < data->time_to_eat)
	{
		if (data->is_dead || is_dead(content))
			return (death_handler(data, index));
	}
	return (1);
}

int	take_fork(void *content, t_data *data, int index)
{
	if (data->num_of_philo == 1)
	{
		while (chronometer() < data->time_to_die)
			;
		printf(BLUE "%ld" CLOSE YELL "\tPhilo\t%d" CLOSE RED
			"\tdied\n" CLOSE, chronometer(), index);
		data->is_dead = 1;
		return (0);
	}
	pthread_mutex_lock(&data->forks[index]);
	pthread_mutex_lock(&data->forks[(index + 1) % data->num_of_philo]);
	if (is_dead(content))
		return (death_handler(data, index));
	action('f', index, data);
	if (!start_eat(content, data, index))
		return (death_handler(data, index));
	if (is_dead(content))
		return (death_handler(data, index));
	pthread_mutex_unlock(&data->forks[index]);
	pthread_mutex_unlock(&data->forks[(index + 1) % data->num_of_philo]);
	return (1);
}

int	start_sleep(void *content, t_data *data, int index)
{
	long	time_start;

	action('s', index, data);
	time_start = chronometer();
	if (data->is_dead || is_dead(content))
		return (death_handler(data, index));
	while (chronometer() - time_start < data->time_to_sleep)
	{
		if (data->is_dead || is_dead(content))
			return (death_handler(data, index));
	}
	return (1);
}
