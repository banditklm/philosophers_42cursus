/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:56:19 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/27 10:28:49 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_printf(t_philo *philo, t_type type, size_t t)
{
	sem_wait(philo->data->print);
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
