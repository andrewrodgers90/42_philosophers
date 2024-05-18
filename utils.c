/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:01:33 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/18 18:56:40 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_try_lock(pthread_mutex_t *mtx)
{
	int	result;

	result = pthread_mutex_lock(mtx);
	return (result);
}

void	write_state(t_philo *philo, int flag)
{
	long	elapsed;

	elapsed = get_time() - philo->start_time;
	pthread_mutex_lock(&philo->data->write_mtx);
	if ((philo->data->philos_dead == 0) && flag == 1)
		printf("%ld %d has taken a fork.\n", elapsed, philo->ph_id);
	else if ((philo->data->philos_dead == 0) && flag == 2)
		printf("%ld %d is eating.\n", elapsed, philo->ph_id);
	else if ((philo->data->philos_dead == 0) && flag == 3)
		printf("%ld %d is sleeping.\n", elapsed, philo->ph_id);
	else if ((philo->data->philos_dead == 0) && flag == 4)
		printf("%ld %d is thinking.\n", elapsed, philo->ph_id);
	else if ((philo->data->philos_dead == 0) && flag == 5)
		printf("%ld %d died.\n", elapsed, philo->ph_id);
	pthread_mutex_unlock(&philo->data->write_mtx);
}
