/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <arodgers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:05:06 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/02 14:37:32 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philo = &table->philos[i];
		pthread_mutex_destroy(&philo->philo_mtx);
		i++;
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		fork = &table->forks[i];
		pthread_mutex_destroy(&fork->fork);
		i++;
	}
	pthread_mutex_destroy(&table->write_mtx);
	pthread_mutex_destroy(&table->table_mtx);
	free(table->philos);
	free(table->forks);
}
