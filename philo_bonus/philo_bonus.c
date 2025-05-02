/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:35:23 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 22:03:18 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_child_processes(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	sem_unlink("/fork");
	sem_unlink("/stop");
	sem_unlink("/log");
	sem_unlink("/forks");
	sem_close(table->fork);
	sem_close(table->log);
	sem_close(table->stop);
	sem_close(table->forks);
	free(philo);
	free(table);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (printf(USAGE"\n"), 1);
	check_args(argc, argv);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	table = memset(table, 0, sizeof(t_table));
	table->philo_count = ft_atoi(argv[1]);
	table->philo_data = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philo_data)
		return (free(table), 1);
	init_args(table->philo_data, argc, argv, table);
	init_philos(table->philo_data, argv, table);
	return (0);
}
