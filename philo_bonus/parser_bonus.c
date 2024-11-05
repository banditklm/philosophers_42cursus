/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelmounj <kelmounj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:20 by kelmounj          #+#    #+#             */
/*   Updated: 2024/11/05 01:17:32 by kelmounj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_num(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		j = 0;
		if (!str[i][j])
			return (0);
		while (str[i][j])
		{
			if (!(str[i][j] == ' ' || str[i][j] == '+'
				|| (str[i][j] >= '0' && str[i][j] <= '9')))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_sign(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '+') && (str[i][j + 1] == '+'
				|| str[i][j + 1] == ' ' || str[i][j + 1] == '\0'))
				return (0);
			else if ((str[i][j] >= '0' && str[i][j] <= '9')
				&& (str[i][j + 1] == '+'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	get_args(char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) > INT_MAX || ft_atoi(av[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	parser(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!is_num(av) || !check_sign(av) || !get_args(av))
			return (0);
		return (1);
	}
	else
		return (0);
}
