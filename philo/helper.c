/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:59:07 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/24 11:53:00 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf(t_philo *philo, t_type type, size_t t)
{
	pthread_mutex_lock(&philo->data->print);
	if (type == THINK)
		printf("%ld %d is thinking\n", t, philo->id);
	if (type == SLEEP)
		printf("%ld %d is sleeping\n", t, philo->id);
	if (type == EAT)
		printf("%ld %d is eating\n", t, philo->id);
	if (type == FORK)
		printf("%ld %d has taken a fork\n", t, philo->id);
	if (type == DEAD)
		printf("%ld %d died\n", t, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

bool	get_flag(t_data *data)
{
	bool	res;

	pthread_mutex_lock(&data->died);
	res = data->dead;
	pthread_mutex_unlock(&data->died);
	return (res);
}

bool	get_meals(t_philo *philo)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->nbr_meals >= philo->must_eat)
		res = true;
	pthread_mutex_unlock(&philo->philo_lock);
	return (res);
}

bool	check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if ((get_tv() - philo->t_last) >= philo->t_die)
	{
		pthread_mutex_lock(&philo->data->died);
		philo->data->dead = true;
		pthread_mutex_unlock(&philo->data->died);
		ft_printf(philo, DEAD, get_tv() - philo->data->t_begin);
		pthread_mutex_unlock(&philo->philo_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (false);
}

bool	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->nbr_meals >= philo->must_eat)
	{
		pthread_mutex_unlock(&philo->philo_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (false);
}
