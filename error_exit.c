/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:40:10 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/17 21:30:37 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_exit(int code, t_table *table, char *str)
{
	int	i;

	if (table)
	{
		if (table->philos)
		{
			free(table->philos);
			table->philos = NULL;
		}
		if (table->forks)
		{
			i = 0;
			while (i < table->philo_count)
			{
				pthread_mutex_destroy(&table->forks[i]);
				i++;
			}
			free(table->forks);
			table->forks = NULL;
		}
	}
	if (str && *str)
		printf("%s", str);
	return (code);
}
