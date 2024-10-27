/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:33:22 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/27 11:02:40 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data			data;

	if (!parser(ac, av))
	{
		printf("Error\n");
		return(1);
	}
	init_args(&data, ac, av);
	data.philos = malloc(data.nbr_philo * sizeof(t_philo));
	if (!data.philos)
	{
		write(2, "Error dallocation\n", 18);
		return (1);
	}
	// pid_t	pid[10];

	// for (int i = 0; i < 10; i++)
	// {
	// 	pid[i] = fork();
	// 	if (pid[i] < 0)
	// 	{
	// 		write(1, "Error fork()\n", 13);
	// 	}
	// 	else if (pid[i] == 0)
	// 	{
	// 		write(1, "i'm the child\n", 14);
	// 	}
	// 	else
	// 	{
	// 		write(1, "i'm the parent\n", 15);
	// 		wait(NULL);
	// 	}
	// }
	// exit(0);
	init_data(&data);
	init_sem(&data);
	init_philo(&data);
}