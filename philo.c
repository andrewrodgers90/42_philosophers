/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arodgers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:16 by arodgers          #+#    #+#             */
/*   Updated: 2024/04/21 18:04:44 by arodgers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	table = malloc(sizeof(t_table));
	if (!table)
	{
		print_error("Malloc error.\n");
		return (1);
	}
	if ((ac == 5 || ac == 6) && parse_args(&table, av) == 0)
	{
		init_data(table);
		dinner(table);
		clean_table(table);
	}
	else
	{
		print_error("Invalid input.\n");
		return (1);
	}
	return (0);
}
