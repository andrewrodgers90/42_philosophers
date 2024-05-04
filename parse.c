/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:19:21 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/21 18:12:03 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_table *table)
{
	if (table->num_of_philos <= 0)
		return (1);
	else if (table->time_to_die <= 0)
		return (1);
	else if (table->time_to_eat <= 0)
		return (1);
	else if (table->time_to_sleep <= 0)
		return (1);
	else
		return (0);
}

int	ft_is_whitespace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

int	ft_overflow_check(int sign)
{
	if (sign == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		sign_counter;
	int		i;
	long	num;

	sign = 1;
	num = 0;
	i = 0;
	sign_counter = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
		sign_counter++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	if (num < 0)
		return (ft_overflow_check(sign));
	if (sign_counter > 1)
		return (0);
	return (num * sign);
}

int	parse_args(t_table **table, char **av)
{
	(*table)->num_of_philos = ft_atoi(av[1]);
	(*table)->time_to_die = ft_atoi(av[2]);
	(*table)->time_to_eat = ft_atoi(av[3]);
	(*table)->time_to_sleep = ft_atoi(av[4]);
	if (check_args(*table) == 1)
		return (1);
	if (av[5])
	{
		(*table)->max_meals = ft_atoi(av[5]);
		if ((*table)->max_meals <= 0)
			return (1);
	}
	else
		(*table)->max_meals = -1;
	return (0);
}
