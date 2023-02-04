/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:34:35 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/13 04:24:14 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	int	ai;

	ai = get_time(philo->data->start);
	pthread_mutex_lock(&philo->data->eating);
	pthread_mutex_lock(&philo->data->last_eat);
	if (ai - philo->last_meal < philo->data->t_die
		|| philo->eaten == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->data->last_eat);
		pthread_mutex_unlock(&philo->data->eating);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->last_eat);
		pthread_mutex_unlock(&philo->data->eating);
	}
	pthread_mutex_lock(&philo->data->varif_dead);
	philo->data->dead = 1;
	pthread_mutex_unlock(&philo->data->varif_dead);
	print_msg(philo, "has died\n", 1);
	return (1);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->fork);
	print_msg(philo, "has taken a fork\n", 0);
	pthread_mutex_lock(&philo->right->fork);
	print_msg(philo, "has taken a fork\n", 0);
}

int	eating(t_philo *philo)
{
	int	i;
	int	value;

	taking_fork(philo);
	pthread_mutex_lock(&philo->data->varif_dead);
	value = philo->data->dead;
	pthread_mutex_unlock(&philo->data->varif_dead);
	if (!value)
	{
		i = get_time(philo->data->start);
		pthread_mutex_lock(&philo->data->last_eat);
		philo->last_meal = i;
		pthread_mutex_unlock(&philo->data->last_eat);
		print_msg(philo, "is eating\n", 0);
		my_usleep(philo->data->t_eat);
		pthread_mutex_lock(&philo->data->eating);
		philo->eaten++;
		pthread_mutex_unlock(&philo->data->eating);
	}
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
	return (0);
}

void	*routine_util(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->data->eating);
	pthread_mutex_lock(&philo->data->max_eat);
	if (philo->eaten == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_unlock(&philo->data->max_eat);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->eating);
	pthread_mutex_unlock(&philo->data->max_eat);
	pthread_mutex_lock(&philo->data->varif_dead);
	value = philo->data->dead;
	pthread_mutex_unlock(&philo->data->varif_dead);
	if (!value)
	{
		print_msg(philo, "is sleeping\n", 0);
		my_usleep(philo->data->t_sleep);
	}
	if (!value)
		print_msg(philo, "is thinking\n", 0);
	if (!value)
		philo_routine(philo);
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int		value;

	philo = ptr;
	pthread_mutex_lock(&philo->data->eating);
	pthread_mutex_lock(&philo->data->max_eat);
	if (philo->eaten == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->data->eating);
		pthread_mutex_unlock(&philo->data->max_eat);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->eating);
	pthread_mutex_unlock(&philo->data->max_eat);
	eating(philo);
	routine_util(philo);
	return (NULL);
}
