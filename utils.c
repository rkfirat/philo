/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 03:14:56 by rfirat            #+#    #+#             */
/*   Updated: 2025/04/17 21:13:36 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	valid_input(char *str)
{
	if (!str || *str == '\0')
		return (printf(NAN), 1);
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (printf(NEGATIVE_VALUE), 1);
	if (*str == '+')
		str++;
	if (!is_digit(*str))
		return (printf(NAN), 1);
	while (*str)
	{
		if (!is_digit(*str))
			return (printf(NAN), 1);
		str++;
	}
	return (0);
}

static long	ft_atol(char *str)
{
	long	res;

	res = 0;
	if (valid_input(str))
		return (-1);
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (is_digit(*str))
		res = res * 10 + (*str++) - '0';
	if (res > INT_MAX)
		return (printf(TOO_BIG), -1);
	return (res);
}

int	parse_input(t_table *table, char **argv)
{
	table->philo_count = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->must_eat = ft_atol(argv[5]);
	else
		table->must_eat = -2;
	if (table->philo_count < 1)
		return (printf(PHILO_COUNT), 1);
	if (table->time_to_die < 60
		|| table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (printf(MIN_TIMESTAMP), 1);
	return (0);
}
