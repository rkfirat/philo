/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:54:49 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/17 21:42:59 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].is_full = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].first_fork = &table->forks[i];
		table->philos[i].second_fork = &table->forks[(i + 1) % table->philo_count];
		table->philos[i].table = table;
		table->philos[i].thread_id = 0;
		i++;
	}
	table->start_sim = 1;
	table->is_finished = 0;
	return (0);
}

int	data_init(t_table *table)
{
	int	i;

	table->is_finished = 0;
	table->start_sim = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (philo_exit(1, table, MALLOC_ERROR));
	table->forks = malloc(sizeof(t_mtx) * table->philo_count);
	if (!table->forks)
		return (philo_exit(1, table, MALLOC_ERROR));
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			table->philo_count = i;
			return (philo_exit(1, table, MALLOC_ERROR));
		}
		i++;
	}
	return (philo_init(table));
}
