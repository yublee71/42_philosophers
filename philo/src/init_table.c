/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:16:55 by yublee            #+#    #+#             */
/*   Updated: 2025/01/19 14:45:28 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	distroy_fork_mutex(t_table *table, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&table->forks_mutex[i]);
}

static int	init_mutex(t_table *table, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (pthread_mutex_init(&table->forks_mutex[i], NULL) != 0)
		{
			distroy_fork_mutex(table, i);
			return (-1);
		}
	}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		distroy_fork_mutex(table, i);
		return (-1);
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		distroy_fork_mutex(table, i);
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
		philo->id = i;
		philo->table = table;
		philo->n_of_eating = 0;
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
	table->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * n);
	if (!table->forks || !table->forks_mutex || !table->philos
		|| init_philos(table, n) < 0)
		return (err_msg(STR_ERR_MALLOC, -1));
	if (init_mutex(table, n) < 0)
		return (err_msg(STR_ERR_MUTEX, -1));
	table->is_dead = 0;
	return (0);
}
