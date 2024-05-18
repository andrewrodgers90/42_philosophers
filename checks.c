/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:59:31 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/18 18:46:42 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_dead(t_philo *philo)
{
	int	res;

	res = get_int(&philo->data->table_mtx, &philo->data->philos_dead);
	return (res);
}

int	philos_full(t_philo *philo)
{
	int	res;

	res = get_int(&philo->data->table_mtx, &philo->data->philos_full);
	if (res == philo->data->philo_num)
		return (1);
	else
		return (0);
}

int	philo_full(t_philo *philo)
{
	int	res;

	res = get_int(&philo->ph_mtx, &philo->meal_count);
	if (res == philo->max_meals)
		return (1);
	else
		return (0);
}

int	philo_dead(t_philo *philo)
{
	long	elapsed;

	elapsed = get_time() - get_long(&philo->ph_mtx, &philo->last_meal);
	if (elapsed > (philo->t_die))
		return (1);
	return (0);
}
