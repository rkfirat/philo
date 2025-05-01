/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:42:32 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 21:44:40 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    ft_usleep(size_t milliseconds)
{
    size_t  start;

    start = get_time();
    while (get_time() - start < milliseconds)
        usleep(1000);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_status(int id, const char *status, t_table *table)
{
	long	timestamp;

	sem_wait(table->log);
	timestamp = get_time() - table->start_time;
	printf("%ld %d %s\n", timestamp, id, status);
	sem_post(table->log);
}
