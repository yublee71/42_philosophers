/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:16:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 16:57:46 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_mutex(t_table *table, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&table->forks_mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks_mutex[i]);
			return (-1);
		}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&table->forks_mutex[i]);
		return (-1);
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&table->forks_mutex[i]);
		pthread_mutex_destroy(&table->death_mutex);
		return (-1);
	}
	return (0);
}

static int	init_philos(t_table *table, int n)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < n)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->philo_num = i;
		philo->table = table;
		table->philos[i] = philo;
		i++;
	}
	return (0);
}

int	init_table(t_table *table, t_info info)
{
	int	n;

	n = info.n_of_philos;
	table->info = info;
	table->forks = (int *)malloc(sizeof(int) * n);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * n);
	table->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!table->forks || !table->forks_mutex || !table->philos)
	{
		free_table(table);
		return (-1);
	}
	if (init_philos(table, n) < 0 || init_mutex(table, n) < 0)
	{
		free_table(table);
		return (-1);
	}
	table->is_dead = 0;
	return (0);
}
