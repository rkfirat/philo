/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:28:35 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/17 21:36:12 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

# define INVALID_ARGS "Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define NEGATIVE_VALUE "All values must be positive\n"
# define NAN "You cannot enter other than numbers\n"
# define TOO_BIG "The value is too big, INT_MAX is the limit\n"
# define PHILO_COUNT "Number of philosophers must be 1 or more\n"
# define MIN_TIMESTAMP "Use timestamps major than 60ms\n"
# define MALLOC_ERROR "Memory Allocation Error\n"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philo {
	int			id;
	long		meals_counter;
	long		is_full;
	long		last_meal;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table {
	int		philo_count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	must_eat;
	long	start_sim;
	long	is_finished;
	t_mtx	*print_mtx;
	t_mtx	*check_mtx;
	t_mtx	*check_eat_mtx;
	t_mtx	*check_death_mtx;
	t_mtx	*forks;
	t_philo	*philos;
}	t_table;

int	parse_input(t_table *table, char **argv);
int	philo_exit(int code, t_table *table, char *str);
int	data_init(t_table *table);

#endif