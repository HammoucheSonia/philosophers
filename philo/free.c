/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:31:39 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/13 04:25:34 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*free_forks(t_info *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (data->forks[i])
		{
			pthread_mutex_destroy(&data->forks[i]->fork);
			free(data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&data->data->print);
	pthread_mutex_destroy(&data->data->varif_dead);
	pthread_mutex_destroy(&data->data->eating);
	pthread_mutex_destroy(&data->data->max_eat);
	pthread_mutex_destroy(&data->data->last_eat);
	pthread_mutex_destroy(&data->data->mutex_nbr);
	free(data->forks);
	return (NULL);
}

t_info	*free_philo(t_info *data)
{
	int	i;

	i = 0;
	if (data->philo)
	{
		while (data->philo[i])
		{
			free(data->philo[i]);
			i++;
		}
	}
	return (NULL);
}

int	free_thread(t_info *data)
{
	int	i;

	i = 0;
	if (!data->data->thread)
		return (0);
	while (i < data->data->nbr)
	{
		if (data->data->thread[i] || !data->data->dead)
		{
			if (pthread_join(data->data->thread[i], NULL))
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

t_info	*free_data(t_info *data)
{
	if (data->data->start)
		free(data->data->start);
	if (data->data)
		free(data->data);
	if (data->philo)
		free(data->philo);
	return (NULL);
}

t_info	*free_all(t_info *data)
{
	if (!data)
		return (NULL);
	if (!data->data)
		return (NULL);
	if (data->data->nbr > 1)
		free_thread(data);
	if (data->data->thread)
		free(data->data->thread);
	free_forks(data);
	free_philo(data);
	free_data(data);
	free(data);
	return (NULL);
}
