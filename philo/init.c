/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:33:59 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/11 13:10:36 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *data, int ac, char **av)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	detach_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_detach(data->philos[i].thread);
		i++;
	}
	return ;
}

int	init_philo(t_data *data)
{
	int		i;

	(1) && (i = 0, data->t_begin = get_tv());
	while (i < data->nbr_philo)
	{
		(1) && (data->philos[i].id = i + 1, data->philos[i].t_die = data->t_die,
		data->philos[i].t_eat = data->t_eat);
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].must_eat = data->must_eat;
		(1) && (data->philos[i].t_last = get_tv(), data->philos[i].n_meal = 0);
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->nbr_philo];
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].philo_lock, NULL);
		if (pthread_create(&data->philos[i].thread, NULL,
				(void *)philo_routine, &data->philos[i]) != 0)
			return (i);
		i++;
	}
	if (data->must_eat == 0)
		return (-1);
	monitor_philos(data);
	detach_thread(data);
	return (-1);
}

void	init_data(t_data *data)
{
	data->dead = false;
	data->has_eat = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->died, NULL);
}
