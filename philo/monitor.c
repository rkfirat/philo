/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:57:40 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/28 20:11:45 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meal_check(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (read_value(table) >= table->philo_count * table->meal_check)
	{
		pthread_mutex_lock(&table->death_check);
		table->is_table_over = 1;
		pthread_mutex_unlock(&table->death_check);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!check_table(table) && table->philo_count > 1)
	{
		i = -1;
		while (++i < table->philo_count)
		{
			pthread_mutex_lock(&table->meal_mutex);
			if (get_time() - table->philo_data[i].last_meal >= \
				table->philo_data[i].time_to_die)
			{
				pthread_mutex_unlock(&table->meal_mutex);
				kill_philo(table->philo_data, table, i);
				return (NULL);
			}
			pthread_mutex_unlock(&table->meal_mutex);
		}
		if (table->meal_check > 0 && meal_check(table->philo_data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
