/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:39:59 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/18 18:51:39 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				ph_id;
	int				meal_count;
	int				max_meals;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	long			start_time;
	long			last_meal;
	pthread_mutex_t	*fork_one;
	pthread_mutex_t	*fork_two;
	pthread_mutex_t	ph_mtx;
	pthread_t		ph_th;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				philo_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	int				philos_full;
	int				philos_dead;
	int				end_dinner;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	*forks;
};

// parse

int		parse_args(t_data *data, char **av);

int		ft_overflow_check(int sign);

int		ft_atoi(const char *str);

// init

void	init_data(t_data *data);

void	init_philos(t_data *data);

void	init_times(t_data *data, int i);

void	init_forks(t_data *data, int i);

// clear_utils

void	clear_table(t_data *data);

// eat_dinner

void	eat_dinner(t_data *data);

void	*dinner_for_one(void *arg);

void	*group_dinner(void *arg);

int		eat(t_philo *philo);

void	eat_meal(t_philo *philo);

int		ft_try_lock(pthread_mutex_t *mtx);

// getters_and_setters

void	set_int(pthread_mutex_t *mtx, int *dest, int value);

int		get_int(pthread_mutex_t *mtx, int *value);

void	set_long(pthread_mutex_t *mtx, long *dest, long value);

long	get_long(pthread_mutex_t *mtx, long *value);

void	increase_count(pthread_mutex_t *mtx, int *count);

// checks

int		philos_dead(t_philo *philo);

int		philos_full(t_philo *philo);

int		philo_full(t_philo *philo);

int		philo_dead(t_philo *philo);

// write_utils

void	write_state(t_philo *philo, int flag);

// chrono_utils

long	get_time(void);

long	get_elapsed(t_philo *philo);

#endif
