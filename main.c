/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:28:24 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/17 21:34:16 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (philo_exit(1, NULL, INVALID_ARGS));
	if (parse_input(&table, argv))
		return (philo_exit(1, &table, ""));
	if (data_init(&table))
		return (philo_exit(1, &table, ""));
	if (table.philo_count == 1)
		printf("%d 1 has taken a fork\n%ld 1 is died\n", 0, table.time_to_die);
	else
		start_simulation(&table);
	philo_exit(0, &table, "");
	return (0);
}
