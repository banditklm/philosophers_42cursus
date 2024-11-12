/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:33:22 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/11 13:36:15 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data			data;

	if (!parser(ac, av))
	{
		printf("Error\n");
		return (1);
	}
	init_args(&data, ac, av);
	data.philos = malloc(data.nbr_philo * sizeof(t_philo));
	if (!data.philos)
	{
		write(2, "Error of allocation\n", 20);
		return (1);
	}
	init_data(&data);
	init_sem(&data);
	init_philo(&data);
}
