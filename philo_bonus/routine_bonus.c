/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:38:49 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 22:03:50 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void* arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_meal >= philo->time_to_die)
		{
			log_status(philo->id, "is dead", philo->table);
			sem_post(philo->table->stop);
		}
		if (philo->table->meal_check > 0
			&& philo->eaten_meal == philo->table->meal_check)
			sem_post(philo->table->stop);
		usleep(1000);
	}
	return (NULL);
}


void	routine(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor, philo) != 0)
		return ;
	while (1)
	{
		log_status(philo->id, "is thinking", philo->table);
		sem_wait(philo->table->forks);
		sem_wait(philo->table->fork);
		sem_post(philo->table->forks);
		log_status(philo->id, "has taken a fork", philo->table);
		sem_wait(philo->table->forks);
		sem_wait(philo->table->fork);
		sem_post(philo->table->forks);
		log_status(philo->id, "has taken a fork", philo->table);
		log_status(philo->id, "is eating", philo->table);
		philo->last_meal = get_time();
		philo->eaten_meal++;
		ft_usleep(philo->time_to_eat);
		sem_post(philo->table->fork);
		sem_post(philo->table->fork);
		log_status(philo->id, "is sleeping", philo->table);
		ft_usleep(philo->time_to_sleep);		
	}
}
