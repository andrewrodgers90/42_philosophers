/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <arodgers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:49:44 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/04 14:06:08 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_for_one(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time());
	increase_count(&philo->table->table_mtx, &philo->table->threads);
	write_state(philo, 1);
	//while (philo->table->end_simulation == 0)
	usleep (philo->table->time_to_die * 1000);
	write_state(philo, 5);
	set_int(&philo->table->table_mtx, &philo->table->end_simulation, 1);
	return (NULL);
}

void	think(t_philo *philo)
{
	int	time_to_think;

	write_state(philo, 4);
	if (philo->table->num_of_philos % 2 == 0)
		return ;
	time_to_think = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	exact_usleep(time_to_think * 0.5, philo->table);
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork->fork);
	write_state(ph, 1);
	pthread_mutex_lock(&ph->right_fork->fork);
	write_state(ph, 1);
	set_long(&ph->philo_mtx, &ph->last_meal_time, get_time());
	ph->meal_count++;
	write_state(ph, 2);
	exact_usleep(ph->table->time_to_eat, ph->table);
	if ((ph->table->max_meals > 0) && (ph->meal_count == ph->table->max_meals))
		set_int(&ph->philo_mtx, &ph->full, 1);
	pthread_mutex_unlock(&ph->left_fork->fork);
	pthread_mutex_unlock(&ph->right_fork->fork);
}

void	*dinner_time(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	synchronise_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time());
	increase_count(&philo->table->table_mtx, &philo->table->threads);
	stagger_start_time(philo);
	while (philo->table->end_simulation == 0)
	{
		if (get_int(&philo->philo_mtx, &philo->full) == 1)
			break ;
		eat(philo);
		write_state(philo, 3);
		exact_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	set_int(&philo->table->table_mtx, &philo->table->end_simulation, 1);
	return (NULL);
}

void	dinner(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	if (table->num_of_philos == 1)
	{
		philo = &table->philos[0];
		pthread_create(&philo->ph_thread_id, NULL, dinner_for_one, philo);
	}
	else
	{
		while (++i < table->num_of_philos)
		{
			philo = &table->philos[i];
			pthread_create(&philo->ph_thread_id, NULL, dinner_time, philo);
		}
	}
	pthread_create(&table->monitor, NULL, monitor_dinner_time, table);
	set_long(&table->table_mtx, &table->simulation_start_time, get_time());
	set_int(&table->table_mtx, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philos[i].ph_thread_id, NULL);
	set_int(&table->table_mtx, &table->end_simulation, 1);
	pthread_join(table->monitor, NULL);
}
