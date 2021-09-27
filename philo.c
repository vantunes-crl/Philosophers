/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantunes <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:52:48 by vantunes          #+#    #+#             */
/*   Updated: 2021/09/16 13:52:51 by vantunes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *content)
{
	t_data	*data;
	int		index;
	int		times_to_eat;

	data = ((t_content *)content)->data;
	index = ((t_content *)content)->philo_id;
	times_to_eat = data->num_times_eat;
	while (times_to_eat--)
	{
		if (!take_fork(content, data, index))
			break ;
		if (!start_sleep(content, data, index))
			break ;
		if (!data->is_dead)
			action('t', index, data);
	}
	if (!data->is_dead)
		action('d', index, data);
	free(content);
	return (NULL);
}

void	mutex_destroy(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			error("destroy thread", data);
	}
	if (pthread_mutex_destroy(&(data->dead)) != 0)
		error("destroy thread", data);
	if (pthread_mutex_destroy(&(data->action)) != 0)
		error("destroy thread", data);
}

void	ft_join(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_join(data->th_id[i], NULL) != 0)
			error("join thread", data);
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_content	*content;
	int			i;

	memset(&data, 0, sizeof(data));
	if (argc != 5 && argc != 6)
	{
		error("Invalid number of args", &data);
		return (-1);
	}
	if (init_data(&data, argv, argc))
		return (-1);
	mutex_init(&data);
	i = -1;
	while (++i < data.num_of_philo)
	{
		content = init_content(&data, i);
		if (pthread_create(&data.th_id[i], NULL,
				&routine, (void *)content) != 0)
			error("create thread", &data);
	}
	ft_join(&data);
	mutex_destroy(&data);
	return (0);
}
