/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:39:10 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 02:14:38 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_exit(t_data *data)
{
	int		i;

	i = 0;
	sem_close(data->fork);
	sem_unlink("/sem_fork");
	sem_close(data->print);
	sem_unlink("/print");
	sem_close(data->dead_sem);
	sem_unlink("/dead_sem");
	while (i < data->nbr_philo)
	{
		sem_close(data->philos[i].meal);
		sem_unlink(data->philos[i].str);
		free(data->philos[i].str);
		i++;
	}
	free(data->philos);
	exit(0);
}

void	*th_monitor(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		sem_wait(philo->meal);
		if ((get_tv() - philo->t_last) >= philo->t_die)
		{
			sem_wait(philo->data->print);
			sem_wait(philo->data->dead_sem);
			philo->data->dead = true;
			sem_post(philo->data->dead_sem);
			printf("\033[1;31m%ld %d died\n",
				get_tv() - philo->data->t_begin, philo->id);
			sem_post(philo->meal);
			exit(0);
		}
		sem_post(philo->meal);
	}
	return (NULL);
}

void	parent_monitor(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	if (data->must_eat == -1)
	{
		waitpid(-1, &status, 0);
		kill_all(data);
	}
	else
	{
		while (i < data->nbr_philo)
		{
			waitpid(-1, &status, 0);
			i++;
		}
	}
	return ;
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			exit(EXIT_FAILURE);
		else if (data->philos[i].pid == 0)
		{
			proc_routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	parent_monitor(data);
	ft_exit(data);
}
