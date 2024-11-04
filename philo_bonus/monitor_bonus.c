/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:39:10 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/04 10:20:04 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_th(t_philo *philo)
{
	while (1)
	{
        sem_wait(philo->meal);
		if ((get_tv() - philo->t_last) >= philo->t_die)
        {
            sem_wait(philo->data->print);
            philo->data->dead = true;
            printf("%zu %d died\n", get_tv() - philo->data->t_begin, philo->id);
			exit(42 + philo->id);
        }
        sem_post(philo->meal);
	}
	return(0);
}

void    parent_monitor(t_data *data)
{
    int has_eat;
    int status;

    has_eat = 0;
    waitpid(-1, &status, 0);
    if (WEXITSTATUS(status) != 42)
        kill_all(data);
    return ;
}
