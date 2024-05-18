/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 17:46:03 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/18 17:46:35 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	time = 0;
	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Error getting time.\n");
		return (-1);
	}
	else
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	get_elapsed(t_philo *philo)
{
	long	elapsed;

	elapsed = get_time() - philo->start_time;
	return (elapsed);
}
