/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:56:37 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/22 18:43:33 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_table *tbl, int i)
{
	tbl->philos[i].right_fork = &tbl->forks[(i + 1) % tbl->num_of_philos];
	tbl->philos[i].left_fork = &tbl->forks[i];
	if (tbl->philos[i].philo_id % 2 == 0)
	{
		tbl->philos[i].right_fork = &tbl->forks[i];
		tbl->philos[i].left_fork = &tbl->forks[(i + 1) % tbl->num_of_philos];
	}
}

void	init_philos(t_table *table)
{
	int		i;
	t_philo	*temp;

	i = 0;
	while (i < table->num_of_philos)
	{
		temp = &table->philos[i];
		temp->philo_id = i + 1;
		temp->meal_count = 0;
		temp->full = 0;
		temp->table = table;
		pthread_mutex_init(&temp->philo_mtx, NULL);
		assign_forks(table, i);
		i++;
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->threads = 0;
	pthread_mutex_init(&table->table_mtx, NULL);
	pthread_mutex_init(&table->write_mtx, NULL);
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	table->forks = malloc(sizeof(t_fork) * table->num_of_philos);
	while (i < table->num_of_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		i++;
	}
	init_philos(table);
}
