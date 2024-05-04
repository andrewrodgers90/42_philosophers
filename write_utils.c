/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:30:10 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/22 17:53:38 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_state(t_philo *philo, int flag)
{
	long	elapsed;

	elapsed = get_time() - philo->table->simulation_start_time;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->table->write_mtx);
	if ((philo->table->end_simulation == 0) && flag == 1)
		printf("%ld %d has taken a fork.\n", elapsed, philo->philo_id);
	else if ((philo->table->end_simulation == 0) && flag == 2)
		printf("%ld %d is eating.\n", elapsed, philo->philo_id);
	else if ((philo->table->end_simulation == 0) && flag == 3)
		printf("%ld %d is sleeping.\n", elapsed, philo->philo_id);
	else if ((philo->table->end_simulation == 0) && flag == 4)
		printf("%ld %d is thinking.\n", elapsed, philo->philo_id);
	else if ((philo->table->end_simulation == 0) && flag == 5)
		printf("%ld %d died.\n", elapsed, philo->philo_id);
	pthread_mutex_unlock(&philo->table->write_mtx);
}
