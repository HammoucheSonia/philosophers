/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shammouc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:47:41 by shammouc          #+#    #+#             */
/*   Updated: 2022/10/08 10:56:57 by shammouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data
{
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	int				dead;
	int				done;
	pthread_mutex_t	print;
	pthread_mutex_t	varif_dead;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	max_eat;
	pthread_mutex_t	eating;
	pthread_mutex_t	mutex_nbr;
	struct timeval	*start;
	pthread_t		*thread;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	int					id;
	int					eaten;
	int					last_meal;
	t_fork				*right;
	t_fork				*left;
	t_data				*data;
}	t_philo;

typedef struct s_info
{
	t_fork			**forks;
	t_philo			**philo;
	t_data			*data;
}	t_info;

int		get_time(struct timeval *start);
t_info	*create_data(void);
t_info	*init_info(int argc, char **argv, t_info *data);
t_info	*free_all(t_info *data);
int		philo_is_dead(t_philo *philo);
void	print_msg(t_philo *philo, char *str, int is_dead);
void	*philo_routine(void *philo);
void	my_usleep(int n);
int		ft_atoi(const char *str);
int		philo_is_dead(t_philo *philo);
void	print_msg(t_philo *philo, char *str, int is_dead);
int		invalid_argc(void);
int		ft_isdigit(int c);
int		parsing_zero(int argc, char **argv);
int		ft_parsing(int argc, char **argv);
int		philo(t_info *data);
int		routine(t_info *data);
int		verify(t_info *data);
t_info	*free_forks(t_info *data);

#endif
