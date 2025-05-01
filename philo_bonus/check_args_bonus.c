/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfirat <rfirat@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:38:56 by rfirat            #+#    #+#             */
/*   Updated: 2025/05/01 22:02:19 by rfirat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr);
}

void	error_message(int i)
{
	if (i == 1)
		printf("Invalid number_of_philosophers\n");
	else if (i == 2)
		printf("Invalid time_to_die\n");
	else if (i == 3)
		printf("Invalid time_to_eat\n");
	else if (i == 4)
		printf("Invalid time_to_sleep\n");
	else if (i == 5)
		printf("Invalid number_of_times_each_philosopher_must_eat\n");
	exit(1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (!ft_atoi(argv[i]) || ft_atoi(argv[i]) < 0)
			return (error_message(i), 1);
		i++;
	}
	if (argc == 6)
		if (!ft_atoi(argv[5]) || ft_atoi(argv[5]) < 0)
			return (error_message(5), 1);
	return (0);
}
