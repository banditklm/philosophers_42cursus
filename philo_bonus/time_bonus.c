/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:47:44 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/04 13:33:12 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_tv(void)
{
	struct timeval	tv;
	size_t			res;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "Error in time\n", 14);
	res = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return (res);
}

void	ft_usleep(size_t time)
{
	size_t	current;

	current = get_tv();
	while ((get_tv() - current) <= time)
		usleep(200);
}
