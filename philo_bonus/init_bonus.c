/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:06:58 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 02:17:53 by kelmounj         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		exit(EXIT_FAILURE);
	sem_unlink("/dead_sem");
	data->dead_sem = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (data->dead_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
}

void	init_philo(t_data *data)
{
	int		i;

	i = 0;
	if (data->must_eat == 0)
		return ;
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
		data->philos[i].str = ft_strjoin("/", ft_itoa(i));
		sem_unlink(data->philos[i].str);
		data->philos[i].meal = sem_open(data->philos[i].str, O_CREAT, 0644, 1);
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
