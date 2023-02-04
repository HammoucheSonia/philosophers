/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:28:47 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/08 10:48:49 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*create_data(void)
{
	t_info	*data;

	data = malloc(sizeof(t_info));
	if (!data)
		return (NULL);
	data->philo = NULL;
	data->forks = NULL;
	return (data);
}

t_info	*init_forks(t_info *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork *) * (data->data->nbr + 1));
	if (!data->forks)
		return (free_all(data));
	while (i < data->data->nbr)
	{
		data->forks[i] = malloc(sizeof(t_fork));
		if (!data->forks[i])
			return (free_all(data));
		pthread_mutex_init(&data->forks[i]->fork, NULL);
		i++;
	}
	data->forks[i] = NULL;
	return (data);
}

t_info	*init_philo(t_info *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo *) * (data->data->nbr + 1));
	if (!data->philo)
		return (free_all(data));
	while (i < data->data->nbr)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (free_all(data));
		data->philo[i]->id = i + 1;
		data->philo[i]->eaten = 0;
		data->philo[i]->last_meal = 0;
		if (i == 0)
			data->philo[i]->left = data->forks[data->data->nbr - 1];
		else
			data->philo[i]->left = data->forks[i - 1];
		data->philo[i]->right = data->forks[i];
		data->philo[i]->data = data->data;
		i++;
	}
	data->philo[i] = NULL;
	return (data);
}

void	init_mutex(t_info *data)
{
	pthread_mutex_init(&data->data->print, NULL);
	pthread_mutex_init(&data->data->varif_dead, NULL);
	pthread_mutex_init(&data->data->eating, NULL);
	pthread_mutex_init(&data->data->max_eat, NULL);
	pthread_mutex_init(&data->data->last_eat, NULL);
	pthread_mutex_init(&data->data->mutex_nbr, NULL);
}

t_info	*init_info(int argc, char **argv, t_info *data)
{
	data->data = malloc(sizeof(t_data));
	if (!data->data)
	{
		free(data);
		return (NULL);
	}
	data->data->start = malloc(sizeof(struct timeval));
	if (!data->data->start)
		return (free_all(data));
	data->data->nbr = ft_atoi(argv[1]);
	data->data->t_die = ft_atoi(argv[2]);
	data->data->t_eat = ft_atoi(argv[3]);
	data->data->t_sleep = ft_atoi(argv[4]);
	data->data->max_meals = -1;
	if (argc == 6)
		data->data->max_meals = ft_atoi(argv[5]);
	data->data->thread = malloc(sizeof(pthread_t) * data->data->nbr);
	if (!data->data->thread)
		return (free_all(data));
	init_mutex(data);
	if (!init_forks(data))
		return (NULL);
	if (!init_philo(data))
		return (NULL);
	return (data);
}
