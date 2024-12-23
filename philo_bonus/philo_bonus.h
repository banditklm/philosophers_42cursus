/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:13 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/11 11:51:53 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/time.h>
# include <stdbool.h>
# include <pthread.h>
# include <signal.h>

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
	pid_t			pid;
	pthread_t		th;
	int				nbr_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	int				must_eat;
	int				nbr_meals;
	bool			dead;
	size_t			t_last;
	t_data			*data;
	sem_t			*meal;
	char			*str;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*dead_sem;
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
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);
void	parent_monitor(t_data *data);
void	kill_all(t_data *data);
void	simulation(t_data *data);
bool	check_dead(t_data *data);
bool	check_nbr_meals(t_philo *philo);
void	*th_monitor(t_philo *philo);

#endif