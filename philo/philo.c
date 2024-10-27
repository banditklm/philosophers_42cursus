/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:25:06 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/24 12:00:05 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

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
		write(2, "Error dallocation\n", 18);
		return (1);
	}
	init_forks(&data);
	init_data(&data);
	init_philo(&data);
}
