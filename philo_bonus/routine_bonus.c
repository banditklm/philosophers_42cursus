/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:53:43 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/04 10:12:21 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	think(t_philo *philo)
{
	long t;
	t = get_tv() - philo->data->t_begin;
	ft_printf(philo, THINK, t);
	return (1);
}

int	nap(t_philo *philo)
{
	ft_printf(philo, SLEEP, get_tv() - philo->data->t_begin);
	ft_usleep(philo->t_sleep);
	return (1);
}

int	dinner(t_philo *philo)
{
	sem_wait(philo->data->fork);//decrement sem_fork (take a fork)
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->t_die);
		sem_post(philo->data->fork);// increment sem_fork
		return (0);
	}
	sem_wait(philo->data->fork);// decrement sem fork (take another fork)
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	ft_printf(philo, EAT, get_tv() - philo->data->t_begin);
	philo->nbr_meals++;
	sem_wait(philo->meal);
	philo->t_last = get_tv();
	sem_post(philo->meal);
	ft_usleep(philo->t_eat);
	sem_post(philo->data->fork);// increment sem_fork
	sem_post(philo->data->fork);// increment sem_fork
	return (1);
}

// void	*monitor_th(t_philo *philo)
// {
// 	long	now;

// 	while (1)
// 	{
// 		// usleep(100);
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

// bool	check_dead(t_philo *philo)
// {
// 	if ((get_tv() - philo->t_last) >= philo->t_die)
// 	{
// 		sem_post(philo->data->death);
// 		return (true);
// 	}
// 	return (false);
// }

void	*monitor(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->meal);
		if ((get_tv() - philo->t_last) >= philo->t_die)
		{
			sem_wait(philo->data->print);
			sem_wait(philo->data->dead_sem);
			philo->data->dead = true;
			sem_post(philo->data->dead_sem);
			printf("%ld %d died\n", get_tv() - philo->data->t_begin, philo->id);
			sem_post(philo->meal);
			exit(0);
		}
		sem_post(philo->meal);
	}
	return (NULL);
}

bool	check_dead(t_data *data)
{
	sem_wait(data->dead_sem);
	if (data->dead == true)
	{
		sem_post(data->dead_sem);
		return (true);
	}
	sem_post(data->dead_sem);
	return (false);
}

bool	check_nbr_meals(t_philo *philo)
{
	if (philo->nbr_meals >= philo->must_eat)
		return (true);
	return (false);
}

void	proc_routine(t_philo *ph)
{
	t_data	*data;
	t_philo	*philo;

	(1) && (philo = (t_philo *)ph, data = philo->data);
	pthread_create(&philo->th, NULL, (void *)monitor, philo);
	pthread_detach(philo->th);
	while (1)
	{
		if (check_dead(data) || !dinner(philo))
			break;
		if ((philo->must_eat != -1) && check_nbr_meals(philo))
			exit(42);
		if (check_dead(data) || !nap(philo))
			break;
		if (check_dead(data) || !think(philo))
			break;
	}
}
