/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:16:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 14:36:53 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	init_mutex(t_table *table, int n)
{
	pthread_mutex_t	*forks_mutex;
	int				i;

	forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
	if (!forks_mutex)
		return (-1);
	i = -1;
	while (++i < n)
		if (pthread_mutex_init(&forks_mutex[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks_mutex[i]);
			free(forks_mutex);
			return (-1);
		}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0 ||
			pthread_mutex_init(&table->print_mutex, NULL) != 0)
		while (i >= 0)
		{
			pthread_mutex_destroy(&forks_mutex[i--]);
			free(forks_mutex);
			return (-1);
		}	
	table->forks_mutex = forks_mutex;
	return (0);
}

int	init_table(t_table *table, t_info info)
{
	int	n;

	n = info.n_of_philos;
	table->info = info;
	table->philos = (pthread_t *)malloc(sizeof(pthread_t) * n);
	table->forks = (int *)malloc(sizeof(int) * n);
	if (!table->philos || !table->forks)
		return (-1);
	table->is_dead = 0;
	if (init_mutex(table, n) < 0)
		return (-1);
	return (0);
}
