/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:47:38 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/03 20:14:50 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stagger_start_time(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
		exact_usleep(30, philo->table);
}

long	all_threads_ready(pthread_mutex_t *mtx, int *threads, int philo_num)
{
	long	value;

	value = 0;
	pthread_mutex_lock(mtx);
	if (*threads == philo_num)
		value = 1;
	pthread_mutex_unlock(mtx);
	return (value);
}

void	increase_count(pthread_mutex_t *mtx, int *count)
{
	pthread_mutex_lock(mtx);
	*count += 1;
	pthread_mutex_unlock(mtx);
}

void	synchronise_threads(t_table *table)
{
	while (get_int(&table->table_mtx, &table->all_threads_ready) == 0)
		;
}
