/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:33:47 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/22 18:42:05 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define L_BLUE  "\033[0;94m"
# define RESET   "\033[0m"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		fork;
}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	int				full;
	long			last_meal_time;
	pthread_mutex_t	philo_mtx;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		ph_thread_id;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				end_simulation;
	int				all_threads_ready;
	int				threads;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long			simulation_start_time;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	write_mtx;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		monitor;
};

// philo_utils.c

void	print_error(char *error_message);

// parse.c

int		ft_overflow_check(int sign);

int		ft_atoi(const char *str);

int		ft_is_whitespace(int c);

int		check_args(t_table *table);

//long	ft_atol(char *str);

int		parse_args(t_table **table, char **av);

// init_utils.c

void	init_data(t_table *table);

void	init_philos(t_table *table);

void	assign_forks(t_table *tbl, int position);

// dinner.c

void	dinner(t_table *table);

void	*dinner_time(void *data);

void	eat(t_philo *philo);

void	think(t_philo *philo);

void	*dinner_for_one(void *data);

// synchro_utils.c

long	all_threads_ready(pthread_mutex_t *mtx, int *threads, int philo_num);

void	synchronise_threads(t_table *table);

void	increase_count(pthread_mutex_t *mtx, int *count);

void	stagger_start_time(t_philo *philo);

// chrono_utils.c

long	get_time(void);

void	exact_usleep(long usec, t_table *table);

// write_utils.c

void	write_state(t_philo *philo, int flag);

// getters_and_setters.c

void	set_int(pthread_mutex_t *mtx, int *dest, int value);

int		get_int(pthread_mutex_t *mtx, int *value);

void	set_long(pthread_mutex_t *mtx, long *dest, long value);

long	get_long(pthread_mutex_t *mtx, long *value);

// monitor.c

void	*monitor_dinner_time(void *data);

int		philo_dead(t_philo *philo);

// clean_utils.c

void	clean_table(t_table *table);

#endif
