/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:13 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/27 10:29:02 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <pthread.h>
# include <signal.h>


typedef enum	e_type
{
	THINK,
	SLEEP,
	EAT,
	FORK,
	DEAD,
}	t_type;

typedef struct	s_data	t_data;

typedef struct	s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		th;
	int				nbr_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	int				nbr_meals;
	size_t			t_last;
	t_data			*data;
}	t_philo;

typedef struct	s_data
{
	t_philo			*philos;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*dead_sem;
	sem_t			*meals_sem;
	sem_t			*death;
	int				nbr_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	size_t			t_begin;
	bool			dead;
	int				has_eat;
}	t_data;


int		parser(int ac, char **av);
long	ft_atoi(const char *str);
void	init_args(t_data *data, int ac, char **av);
void	init_data(t_data *data);
size_t	get_tv(void);
void	ft_usleep(size_t time);
void	init_sem(t_data *data);
void	init_philo(t_data *data);
void	proc_routine(t_philo *ph);
void	ft_printf(t_philo *philo, t_type type, size_t t);
bool	get_flag(t_data *data);
#endif