/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:53:43 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 02:22:21 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	think(t_philo *philo)
{
	ft_printf(philo, THINK, get_tv() - philo->data->t_begin);
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
	sem_wait(philo->data->fork);
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	if (philo->data->nbr_philo == 1)
	{
		ft_usleep(philo->t_die);
		sem_post(philo->data->fork);
		return (0);
	}
	sem_wait(philo->data->fork);
	ft_printf(philo, FORK, get_tv() - philo->data->t_begin);
	ft_printf(philo, EAT, get_tv() - philo->data->t_begin);
	philo->nbr_meals++;
	sem_wait(philo->meal);
	philo->t_last = get_tv();
	sem_post(philo->meal);
	ft_usleep(philo->t_eat);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	return (1);
}

void	proc_routine(t_philo *ph)
{
	t_data	*data;
	t_philo	*philo;

	(1) && (philo = (t_philo *)ph, data = philo->data);
	pthread_create(&philo->th, NULL, (void *)th_monitor, philo);
	pthread_detach(philo->th);
	while (1)
	{
		if (check_dead(data) || !dinner(philo))
			break ;
		if ((philo->must_eat != -1) && check_nbr_meals(philo))
			exit(0);
		if (check_dead(data) || !nap(philo))
			break ;
		if (check_dead(data) || !think(philo))
			break ;
	}
}
