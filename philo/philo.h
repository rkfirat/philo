/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:35:31 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/30 07:51:34 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int				id;
	int				eaten_meal;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	long			last_meal;
	t_mtx			*first_fork;
	t_mtx			*second_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	pthread_t		monitor;
	pthread_t		*philo_thread;
	struct s_philo	*philo_data;
	int				philo_count;
	long			start_time;
	int				is_table_over;
	int				meal_check;
	int				total_meal;
	t_mtx			*forks;
	t_mtx			log_mutex;
	t_mtx			meal_mutex;
	t_mtx			death_check;
}	t_table;

int		check_args(int argc, char **argv, t_table *table);
long	get_time(void);
int		init_data(t_table *table, char **argv);
int		ft_atoi(char *str);
void	*routine(void *arg);
void	one_philo(t_table *table, t_philo *philo);
int		check_table(t_table *table);
void	log_status(int id, const char *status, t_table *table);
int		read_value(t_table *table);
void	*monitor(void *arg);
void	kill_philo(t_philo *philos, t_table *table, int i);

#endif