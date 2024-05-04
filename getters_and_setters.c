/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:37:09 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/17 18:02:07 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mtx, int *dest, int value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

int	get_int(pthread_mutex_t *mtx, int *value)
{
	int	num;

	pthread_mutex_lock(mtx);
	num = *value;
	pthread_mutex_unlock(mtx);
	return (num);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

long	get_long(pthread_mutex_t *mtx, long *value)
{
	long	num;

	pthread_mutex_lock(mtx);
	num = *value;
	pthread_mutex_unlock(mtx);
	return (num);
}
