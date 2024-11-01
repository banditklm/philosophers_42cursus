/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:06:58 by kelmounj          #+#    #+#             */
/*   Updated: 2024/10/28 10:07:10 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	init_sem(t_data *data)
{
	sem_unlink("/sem_fork");
	data->fork = sem_open("/sem_fork", O_CREAT, 0644, data->nbr_philo);
	if (data->fork == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, 0644, 1);//for printing the messages
	if (data->print == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/dead_sem");
	data->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);//for check dead flag is true
	if (data->dead_sem == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/meals_sem");
	data->meals_sem = sem_open("/dead_sem", O_CREAT, 0644, 0);
	if (data->meals_sem == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	sem_unlink("/death");
	data->death = sem_open("/death", O_CREAT, 0644, 0);
	if (data->death == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
}

void	simulation(t_data *data)
{
	int	pid;
	int	i;
	int status;

	i = 0;
	pid = 0;
	while (i < data->nbr_philo)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork() Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// printf("====>%d<=====\n", data->philos[i].id);
			proc_routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			data->philos[i].pid = pid;
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		waitpid(data->philos[i].pid, &status, 0);
		i++;
	}
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

void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	data->t_begin = get_tv();
	while (i < data->nbr_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].t_die = data->t_die;
		data->philos[i].t_eat = data->t_eat;
		data->philos[i].t_sleep = data->t_sleep;
		data->philos[i].must_eat = data->must_eat;
		data->philos[i].nbr_meals = 0;
		data->philos[i].t_last = get_tv();
		data->philos[i].data = data;
		i++;
	}
	simulation(data);
}
void	init_data(t_data *data)
{
	data->dead = false;
	data->has_eat = 0;
}







	// if (sem_wait(data->death) == 0)
	// 	kill_all(data);
	// if (sem_wait(data->meals_sem) == 0)
	// 	kill_all(data);
	// monitor_philo(data);