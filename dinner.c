/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:17:43 by arodgers          #+#    #+#             */
/*   Updated: 2024/08/09 18:04:33 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_for_one(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start_time = get_time();
	data->philos[0].start_time = data->start_time;
	pthread_mutex_lock(data->philos[0].fork_one);
	write_state(&data->philos[0], TAKE_FORK);
	usleep(data->t_die * 1000);
	pthread_mutex_unlock(data->philos[0].fork_one);
	write_state(&data->philos[0], DEAD);
	return (NULL);
}

void	*group_dinner(void *arg)
{
	t_philo	*philo;
	int		res;

	philo = (t_philo *)arg;
	philo->last_meal = philo->start_time;
	while (philos_dead(philo) == 0)
	{
		if (philo->ph_id % 2 == 0)
			usleep(philo->t_sleep * 1000);
		res = eat(philo);
		if (res)
		{
			write_state(philo, DEAD);
			set_int(&philo->data->table_mtx, &philo->data->philos_dead, 1);
		}
		if (philos_full(philo))
			break ;
		write_state(philo, SLEEP);
		usleep(philo->t_sleep * 1000);
		write_state(philo, THINK);
		usleep((philo->t_eat * 2 - philo->t_sleep) * 1000);
	}
	return (NULL);
}

void	eat_meal(t_philo *philo)
{
	write_state(philo, TAKE_FORK);
	write_state(philo, EAT);
	philo->last_meal = get_time();
	usleep(philo->t_eat * 1000);
	pthread_mutex_unlock(philo->fork_two);
	pthread_mutex_unlock(philo->fork_one);
	increase_count(&philo->ph_mtx, &philo->meal_count);
	if (philo->max_meals > 0 && philo_full(philo))
	{
		increase_count(&philo->data->table_mtx, &philo->data->philos_full);
		if (philos_full(philo))
			return ;
	}
	set_long(&philo->ph_mtx, &philo->last_meal, get_time());
}

int	eat(t_philo *philo)
{
	if (philo_dead(philo))
		return (1);
	if (ft_try_lock(philo->fork_one) != 0)
		return (0);
	write_state(philo, TAKE_FORK);
	if (ft_try_lock(philo->fork_two) != 0)
	{
		pthread_mutex_unlock(philo->fork_one);
		return (0);
	}
	else
		eat_meal(philo);
	return (0);
}

void	eat_dinner(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	if (data->philo_num == 1)
		pthread_create(&data->philos[0].ph_th, NULL, dinner_for_one, data);
	else
	{
		while (++i < data->philo_num)
		{
			philo = &data->philos[i];
			set_long(&data->table_mtx, &data->start_time, get_time());
			set_long(&philo->ph_mtx, &philo->start_time, data->start_time);
			pthread_create(&philo->ph_th, NULL, group_dinner, philo);
		}
	}
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].ph_th, NULL);
}
