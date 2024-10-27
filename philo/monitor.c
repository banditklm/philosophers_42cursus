/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:58:12 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/26 11:51:01 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philos0(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		data->has_eat = 0;
		while (i < data->nbr_philo)
		{
			if (check_died(&data->philos[i]))
				return (NULL);
			if (check_meals(&data->philos[i]))
				data->has_eat++;
			i++;
		}
		if (data->has_eat == data->nbr_philo)
			break ;
		usleep(50);
	}
	return (0);
}

void	*monitor_philos1(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->nbr_philo)
			i = 0;
		if (check_died(&data->philos[i]))
			break ;
		i++;
	}
	return (0);
}
