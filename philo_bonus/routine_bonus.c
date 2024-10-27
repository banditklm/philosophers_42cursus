/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:53:43 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/27 10:51:39 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// bool	get_flag(t_data *data)
// {
// 	bool	res;

// 	res = data->dead;
// 	return (res);
// }

void	think(t_philo *philo)
{
	long t;

	t = get_tv() - philo->data->t_begin;
	ft_printf(philo, THINK, t);
}

void 	nap(t_philo *philo)
{
	ft_printf(philo, SLEEP, get_tv() - philo->data->t_begin);
	ft_usleep(philo->t_sleep);
}

void	dinner(t_philo *philo)
{
	sem_wait(philo->data->fork);//decrement sem_fork (take a fork)
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->t_die);
		sem_post(philo->data->fork);// increment sem_fork
		return;
	}
	sem_wait(philo->data->fork);// decrement sem fork (take another fork)
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	ft_printf(philo, EAT, get_tv() - philo->data->t_begin);
	philo->nbr_meals++;
	philo->t_last = get_tv();
	ft_usleep(philo->t_eat);
	sem_post(philo->data->fork);// increment sem_fork
	sem_post(philo->data->fork);// increment sem_fork
}

// void	*monitor_th(t_philo *philo)
// {
// 	long	now;

// 	while (1)
// 	{
// 		usleep(100);
// 		now = get_tv();
// 		// while (!philo->data->dead && philo->data->has_eat < philo->nbr_philo)
// 		// {
// 		if ((now - philo->t_last) >= philo->t_die)
// 		{
// 			sem_wait(philo->data->dead_sem);
// 			philo->data->dead = true;
// 			sem_post(philo->data->dead_sem);
// 			break;
// 		}
// 		if (philo->nbr_meals >= philo->must_eat)
// 		{
// 			sem_wait(philo->data->meals_sem);
// 			philo->data->has_eat++;
// 			sem_post(philo->data->meals_sem);
// 			if (philo->data->has_eat >= philo->data->nbr_philo)
// 				break;
// 		}
// 		// }
// 	}
// 	return(0);
// }

bool	check_dead(t_philo *philo)
{
	if ((get_tv() - philo->t_last) >= philo->t_die)
	{
		sem_post(philo->data->death);
		return (true);
	}
	return (false);
}

void	proc_routine(t_philo *ph)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)ph;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		dinner(philo);
		// if (philo->nbr_meals >= philo->must_eat)
		// 	sem_post(data->meals_sem);
		// if (philo->nbr_meals >= philo->must_eat)
			// sem_post(data->meals_sem);
		nap(philo);
		// if (philo->nbr_meals >= philo->must_eat)
			// sem_post(data->meals_sem);
		think(philo);
	}
	// pthread_join(philo->th, NULL);
}
