/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:08:25 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/04 14:01:34 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	long	elapsed;

	if (get_int(&philo->philo_mtx, &philo->full) == 1)
		return (0);
	elapsed = get_time() - get_long(&philo->philo_mtx, &philo->last_meal_time);
	if (elapsed > (philo->table->time_to_die))
		return (1);
	return (0);
}

void	*monitor_dinner_time(void *data)
{
	t_table	*t;
	int		i;

	t = (t_table *)data;
	while (all_threads_ready(&t->table_mtx, &t->threads, t->num_of_philos) == 0)
		;
	while (t->end_simulation == 0)
	{
		if (t->num_of_philos > 1)
		{
			i = 0;
			while ((i < t->num_of_philos) && (t->end_simulation == 0))
			{
				if (philo_dead(&t->philos[i]) == 1)
				{
					write_state(&t->philos[i], 5);
					set_int(&t->table_mtx, &t->end_simulation, 1);
				}
				i++;
			}
		}
	}
	set_int(&t->table_mtx, &t->end_simulation, 1);
	return (NULL);
}
