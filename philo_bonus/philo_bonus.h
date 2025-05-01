/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:35:31 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 22:02:50 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define USAGE "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef struct s_table	t_table;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			eaten_meal;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_die;
	long		last_meal;
	t_table		*table;
	pthread_t	monitor;
}	t_philo;

typedef struct s_table
{
	t_philo	*philo_data;
	int		philo_count;
	long	start_time;
	int		meal_check;
	sem_t	*log;
	sem_t	*fork;
	sem_t	*forks;
	sem_t	*stop;
}	t_table;

int		check_args(int argc, char **argv);
long	get_time(void);
int		ft_atoi(char *str);
void	init_args(t_philo *philo, int argc, char **argv, t_table *table);
void	init_philos(t_philo *philo, char **argv, t_table *table);
void	log_status(int id, const char *status, t_table *table);
void    ft_usleep(size_t milliseconds);
void	routine(t_philo *philo);
void	kill_child_processes(t_table *table, t_philo *philo);

#endif