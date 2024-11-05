/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:58:12 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/04 20:06:47 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philos(t_data *data)
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
			if (data->must_eat != -1 && check_meals(&data->philos[i]))
				data->has_eat++;
			i++;
		}
		if (data->must_eat != -1 && data->has_eat == data->nbr_philo)
			break ;
	}
	return (0);
}
