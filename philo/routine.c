/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:43:13 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/26 13:20:45 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	long	t;

	t = get_tv() - philo->data->t_begin;
	ft_printf(philo, THINK, t);
}

void	nap(t_philo *philo)
{
	ft_printf(philo, SLEEP, get_tv() - philo->data->t_begin);
	ft_usleep(philo->t_sleep, philo->data);
}

void	dinner(t_philo *philo)
{
	pthread_mutex_lock((philo->left_fork));
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->t_die, philo->data);
		pthread_mutex_unlock((philo->left_fork));
		return ;
	}
	pthread_mutex_lock((philo->right_fork));
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	ft_printf(philo, EAT, get_tv() - philo->data->t_begin);
	pthread_mutex_lock(&philo->philo_lock);
	philo->nbr_meals++;
	philo->t_last = get_tv();
	pthread_mutex_unlock(&philo->philo_lock);
	ft_usleep(philo->t_eat, philo->data);
	pthread_mutex_unlock((philo->left_fork));
	pthread_mutex_unlock((philo->right_fork));
}

void	*philo_routine0(void *ph)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)ph;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(180);
	while (1)
	{
		dinner(philo);
		if (get_flag(data) || get_meals(philo))
			break ;
		nap(philo);
		if (get_flag(data) || get_meals(philo))
			break ;
		think(philo);
		if (get_flag(data) || get_meals(philo))
			break ;
	}
	return (0);
}

void	*philo_routine1(void *ph)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)ph;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(180);
	while (1)
	{
		dinner(philo);
		if (get_flag(data))
			break ;
		nap(philo);
		if (get_flag(data))
			break ;
		think(philo);
		if (get_flag(data))
			break ;
	}
	return (0);
}
