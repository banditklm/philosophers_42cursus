/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:25:06 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 02:06:03 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_0(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->died);
	free(data->philos);
	free(data->forks);
}

void	ft_exit_1(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->died);
	free(data->forks);
	free(data->philos);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		val;

	if (!parser(ac, av))
	{
		printf("Error\n");
		return (1);
	}
	init_args(&data, ac, av);
	data.forks = malloc(data.nbr_philo * sizeof(pthread_mutex_t));
	data.philos = malloc(data.nbr_philo * sizeof(t_philo));
	if (!data.forks || !data.philos)
	{
		write(2, "Error of allocation\n", 20);
		return (1);
	}
	init_forks(&data);
	init_data(&data);
	val = init_philo(&data);
	if (val != -1)
		ft_exit_1(&data, val);
	ft_exit_0(&data);
	return (0);
}
