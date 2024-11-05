/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:56:19 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 02:11:59 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_printf(t_philo *philo, t_type type, size_t t)
{
	sem_wait(philo->data->print);
	if (type == THINK)
		printf("\033[0;33m%ld %d is thinking\n", t, philo->id);
	if (type == SLEEP)
		printf("\033[0;30m%ld %d is sleeping\n", t, philo->id);
	if (type == EAT)
		printf("\033[32m%ld %d is eating\n", t, philo->id);
	if (type == FORK)
		printf("\033[0;36m%ld %d has taken a fork\n", t, philo->id);
	sem_post(philo->data->print);
}

bool	get_flag(t_data *data)
{
	bool	res;

	sem_wait(data->dead_sem);
	res = data->dead;
	sem_post(data->dead_sem);
	return (res);
}

void	kill_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nbr_philo)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
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
