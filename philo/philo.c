/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:35:23 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/30 14:27:31 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->death_check);
	free(table->philo_data);
	free(table->forks);
	free(table->philo_thread);
	free(table);
}

int	allocate_dft(t_table *table)
{
	table->philo_data = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philo_data)
		return (free(table), 1);
	table->forks = malloc(sizeof(t_mtx) * table->philo_count);
	if (!table->forks)
		return (free(table->philo_data), free(table), 1);
	table->philo_thread = malloc(sizeof(pthread_t) * table->philo_count);
	if (!table->philo_thread)
		return (free(table->philo_data), free(table->forks), free(table), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		i;
	t_table	*table;

	i = 0;
	if (argc != 5 && argc != 6)
		return (printf(USAGE"\n"), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	table = memset(table, 0, sizeof(t_table));
	if (check_args(argc, argv, table))
		return (1);
	if (allocate_dft(table))
		return (1);
	if (init_data(table, argv))
		return (1);
	i = 0;
	if (pthread_create(&(table->monitor), \
	NULL, monitor, table) != 0)
		return (destroy_table(table), 1);
	while (i < table->philo_count)
		pthread_join(table->philo_thread[i++], NULL);
	pthread_join(table->monitor, NULL);
	destroy_table(table);
	return (0);
}
