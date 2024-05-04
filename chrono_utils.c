/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:12:13 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/04 14:07:04 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exact_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time();
	while (get_time() - start < usec)
	{
		if (table->end_simulation != 0)
			break ;
		elapsed = get_time() - start;
		remaining = usec - elapsed;
		if (remaining > 1000)
			usleep(remaining * 1000 / 2);
		else
		{
			while (get_time() - start < usec)
				;
		}
	}
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	time = 0;
	if (gettimeofday(&tv, NULL) == -1)
		print_error("Error getting time.");
	else
	{
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	return (time);
}
