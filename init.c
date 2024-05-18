/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:20:28 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/18 18:55:13 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_data *data, int i)
{
	t_philo	*temp;
	int		num;

	temp = &data->philos[i];
	num = data->philo_num;
	if (i % 2 == 0)
	{
		temp->fork_one = &data->forks[i];
		temp->fork_two = &data->forks[(i + 1) % num];
	}
	else
	{
		temp->fork_one = &data->forks[(i - 1 + num) % num];
		temp->fork_two = &data->forks[i];
	}
}

void	init_times(t_data *data, int i)
{
	data->philos[i].t_die = data->t_die;
	data->philos[i].t_eat = data->t_eat;
	data->philos[i].t_sleep = data->t_sleep;
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].ph_id = i + 1;
		data->philos[i].meal_count = 0;
		data->philos[i].max_meals = data->max_meals;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].ph_mtx, NULL);
		init_times(data, i);
		init_forks(data, i);
	}
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = 0;
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
	init_philos(data);
}
