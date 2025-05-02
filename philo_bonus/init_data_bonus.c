/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:07:25 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 22:03:09 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_args(t_philo *philo, int argc, char **argv, t_table *table)
{
	if (argc == 6)
		table->meal_check = ft_atoi(argv[5]);
	else
		table->meal_check = 0;
	sem_unlink("/fork");
	sem_unlink("/forks");
	sem_unlink("/log");
	sem_unlink("/stop");
	if (table->forks == SEM_FAILED)
		return (sem_close(table->fork), printf("sem_open /forks"),
			free(philo), free(table), exit(1));
	table->log = sem_open("/log", O_CREAT, 0644, 1);
	if (table->log == SEM_FAILED)
		return (sem_close(table->forks), sem_close(table->fork),
			printf("sem_open /log"), free(philo),
			free(table), exit(1));
	table->stop = sem_open("/stop", O_CREAT, 0644, 0);
	if (table->stop == SEM_FAILED)
		return (sem_close(table->log), sem_close(table->forks),
			sem_close(table->fork), printf("sem_open /stop"),
			free(philo), free(table), exit(1));
}

void	init_child_processes(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
		{
			while (i--)
				if (philo[i].pid > 0)
					kill(philo[i].pid, SIGKILL);
			sem_close(table->fork);
			sem_close(table->forks),
			sem_close(table->log);
			sem_close(table->stop);
			free(philo);
			free(table);
			exit(1);
		}
		if (philo[i].pid == 0)
			routine(&philo[i]);
		usleep(500);
		i++;
	}
}

void	init_philos(t_philo *philo, char **argv, t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->philo_count)
	{
		philo[i].eaten_meal = 0;
		philo[i].last_meal = table->start_time;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].id = i + 1;
		philo[i].table = table;
		i++;
	}
	init_child_processes(philo, table);
	sem_wait(table->stop);
	kill_child_processes(table, philo);
}
