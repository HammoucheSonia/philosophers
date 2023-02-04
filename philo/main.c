/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:46:07 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/08 11:56:19 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	verify(t_info *data)
{
	int	i;
	int	ret;
	int	max;
	int	n_eat;

	i = 0;
	ret = 0;
	while (i < data->data->nbr)
	{
		pthread_mutex_lock(&data->data->eating);
		pthread_mutex_lock(&data->data->max_eat);
		if (data->philo[i]->eaten == data->data->max_meals)
		{
			pthread_mutex_unlock(&data->data->eating);
			pthread_mutex_unlock(&data->data->max_eat);
			ret++;
		}
		else
		{
			pthread_mutex_unlock(&data->data->eating);
			pthread_mutex_unlock(&data->data->max_eat);
		}
		i++;
	}
	return (ret);
}

int	routine(t_info *data)
{
	int	i;

	i = 0;
	if (data->data->nbr == 1)
	{
		print_msg(data->philo[0], "has taken a fork\n", 0);
		pthread_mutex_lock(&data->data->varif_dead);
		data->data->dead = 1;
		pthread_mutex_unlock(&data->data->varif_dead);
		usleep(data->data->t_die * 1000);
		print_msg(data->philo[0], "has died\n", 1);
		return (0);
	}
	while (i < data->data->nbr)
	{
		if (pthread_create(&data->data->thread[i],
				NULL, philo_routine, (void *)data->philo[i]))
			return (1);
		usleep(50);
		i++;
	}
	return (0);
}

void	philo_util(t_info *data, int value, int i)
{
	while (!value)
	{
		i = 0;
		data->data->done = verify(data);
		if (data->data->done == data->data->nbr)
		{
			printf("dinner is over\n");
			break ;
		}
		pthread_mutex_lock(&data->data->mutex_nbr);
		while (i < data->data->nbr)
		{
			my_usleep(10);
			if (!value)
				value = philo_is_dead(data->philo[i]);
			i++;
		}
		pthread_mutex_unlock(&data->data->mutex_nbr);
	}
}

int	philo(t_info *data)
{
	int	i;
	int	value;
	int	n;

	i = 0;
	n = data->data->nbr;
	data->data->dead = 0;
	data->data->done = 0;
	gettimeofday(data->data->start, NULL);
	if (routine(data))
		return (0);
	n = data->data->nbr;
	pthread_mutex_lock(&data->data->varif_dead);
	value = data->data->dead;
	pthread_mutex_unlock(&data->data->varif_dead);
	philo_util(data, value, i);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	*data;
	int		n;

	if (argc == 5 || argc == 6)
	{
		if (ft_parsing(argc, argv))
			return (invalid_argc());
		data = create_data();
		if (!data)
			return (1);
		if (!init_info(argc, argv, data))
			return (1);
		philo(data);
		free_all(data);
	}
	else
		return (invalid_argc());
	return (0);
}
