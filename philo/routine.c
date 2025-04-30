/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:28:45 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/30 14:31:36 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < milliseconds && check_table(table) == 0)
		usleep(500);
}

void	one_philo(t_table *table, t_philo *philo)
{
	log_status(philo->id, "is thinking", table);
	log_status(philo->id, "has taken a fork", table);
	ft_usleep(philo->time_to_die, table);
	printf("%ld %d died", get_time() - table->start_time, philo->id);
	table->is_table_over = 1;
	return ;
}

void	pick_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->first_fork);
		log_status(philo->id, "has taken a fork", philo->table);
		pthread_mutex_lock(philo->second_fork);
		log_status(philo->id, "has taken a fork", philo->table);
	}
	else
	{
		pthread_mutex_lock(philo->second_fork);
		log_status(philo->id, "has taken a fork", philo->table);
		pthread_mutex_lock(philo->first_fork);
		log_status(philo->id, "has taken a fork", philo->table);
	}
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pick_fork(philo);
	log_status(philo->id, "is eating", table);
	pthread_mutex_lock(&table->meal_mutex);
	philo->eaten_meal++;
	table->total_meal++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&table->meal_mutex);
	ft_usleep(philo->time_to_eat, table);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (table->philo_count == 1)
	{
		one_philo(table, philo);
		return (NULL);
	}
	while (check_table(table) == 0)
	{
		eat(philo);
		log_status(philo->id, "is sleeping", table);
		ft_usleep(philo->time_to_sleep, table);
		log_status(philo->id, "is thinking", table);
	}
	return (NULL);
}
