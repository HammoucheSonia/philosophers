/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:04:54 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/08 10:47:09 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, char *str, int is_dead)
{
	int	i;

	i = get_time(philo->data->start);
	pthread_mutex_lock(&philo->data->varif_dead);
	if (!philo->data->dead || is_dead)
	{
		pthread_mutex_unlock(&philo->data->varif_dead);
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d %s", i, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	else
		pthread_mutex_unlock(&philo->data->varif_dead);
}

void	my_usleep(int ms)
{
	struct timeval	sleep;

	gettimeofday(&sleep, NULL);
	while (get_time(&sleep) < ms)
		usleep(100);
}

int	invalid_argc(void)
{
	printf("Arguments are not valid\n");
	return (1);
}

int	get_time(struct timeval *start)
{
	struct timeval		the_start;
	int					i;
	int					j;

	gettimeofday(&the_start, NULL);
	i = (start->tv_usec / 1000) + (start->tv_sec * 1000);
	j = (the_start.tv_usec / 1000) + (the_start.tv_sec * 1000);
	return (j - i);
}
