/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:25:48 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 00:45:01 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef enum e_type
{
	THINK,
	SLEEP,
	EAT,
	FORK,
	DEAD,
}	t_type;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_lock;
	size_t			t_last;
	int				n_meal;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nbr_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	bool			dead;
	size_t			t_begin;
	int				has_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	died;
}	t_data;

int		parser(int ac, char **av);
long	ft_atoi(const char *str);
size_t	get_tv(void);
void	ft_usleep(size_t time, t_data *data);
void	init_args(t_data *data, int ac, char **av);
void	init_forks(t_data *data);
void	*philo_routine(void *philo);
int		init_philo(t_data *data);
void	init_data(t_data *data);
void	ft_printf(t_philo *philo, t_type type, size_t t);
bool	check_died(t_philo *philo);
bool	check_meals(t_philo *philo);
bool	get_flag(t_data *data);
bool	get_meals(t_philo *philo);
void	*monitor_philos(t_data *data);

#endif