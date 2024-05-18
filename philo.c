/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:38:05 by arodgers          #+#    #+#             */
/*   Updated: 2024/05/13 13:18:24 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (ac == 5 || ac == 6)
	{
		if (parse_args(data, av) == 0)
		{
			init_data(data);
			eat_dinner(data);
			clear_table(data);
		}
		else
		{
			printf("Invalid input.\n");
			return (1);
		}
	}
	else
	{
		printf("Invalid input.\n");
		return (1);
	}
	return (0);
}
