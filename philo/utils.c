/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:25 by rfirat            #+#    #+#             */
/*   Updated: 2025/06/26 00:45:07 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_status(int id, const char *status, t_table *table)
{
	long	timestamp;

	pthread_mutex_lock(&table->log_mutex);
	timestamp = get_time() - table->start_time;
	if (check_table(table) == 0)
		printf("%ld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&table->log_mutex);
}

int	read_value(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->meal_mutex);
	value = table->total_meal;
	pthread_mutex_unlock(&table->meal_mutex);
	return (value);
}

int	check_table(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->death_check);
	value = table->is_table_over;
	pthread_mutex_unlock(&table->death_check);
	return (value);
}

void	kill_philo(t_philo *philos, t_table *table, int i)
{
	long	time;

	pthread_mutex_lock(&table->death_check);
	philos->table->is_table_over = 1;
	time = get_time() - philos->table->start_time;
	pthread_mutex_lock(&table->log_mutex);
	printf("%ld %d died\n", time, philos[i].id);
	pthread_mutex_unlock(&table->log_mutex);
	pthread_mutex_unlock(&table->death_check);
}
