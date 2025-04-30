/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:16:32 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/28 20:21:13 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philos(t_table *table, int i)
{
	while (--i >= 0)
		pthread_detach(table->philo_thread[i]);
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

int	init_thread(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		philo[i].first_fork = &table->forks[i];
		philo[i].second_fork = &table->forks[(i + 1) % table->philo_count];
		if (pthread_create(&table->philo_thread[i], NULL, routine, \
			&philo[i]) != 0)
			return (destroy_philos(table, i), 1);
		usleep(1);
		i++;
	}
	return (0);
}

int	mutex_init(t_table *table)
{
	int	log_mutex;
	int	meal_mutex;
	int	death_check;

	log_mutex = pthread_mutex_init(&table->log_mutex, NULL);
	if (log_mutex != 0)
		return (free(table->philo_data), free(table->forks),
			free(table->philo_thread), free(table), 1);
	meal_mutex = pthread_mutex_init(&table->meal_mutex, NULL);
	if (meal_mutex != 0)
		return (pthread_mutex_destroy(&table->log_mutex),
			free(table->philo_data), free(table->forks),
			free(table->philo_thread), free(table), 1);
	death_check = pthread_mutex_init(&table->death_check, NULL);
	if (death_check != 0)
		return (pthread_mutex_destroy(&table->log_mutex),
			pthread_mutex_destroy(&table->meal_mutex),
			free(table->philo_data), free(table->forks),
			free(table->philo_thread), free(table), 1);
	return (0);
}

void	init_arg(t_philo *philo, char **argv, t_table *table)
{
	int	i;

	i = 0;
	table->is_table_over = 0;
	table->total_meal = 0;
	table->start_time = get_time();
	while (i < table->philo_count)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].table = table;
		philo[i].eaten_meal = 0;
		philo[i].last_meal = table->start_time;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].id = i + 1;
		i++;
	}
}

int	init_data(t_table *table, char **argv)
{
	init_arg(table->philo_data, argv, table);
	if (mutex_init(table))
		return (1);
	if (init_thread(table->philo_data, table))
		return (1);
	return (0);
}
