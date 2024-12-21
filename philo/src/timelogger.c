/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timelogger.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:23 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 18:53:11 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*timelogger(void *arg)
{
	t_table	*table;
	t_philo **philos;
	t_philo *philo;
	t_info	info;
	int		i;
	int		n;

	table = (t_table *)arg;
	philos = table->philos;
	info = table->info;
	n = table->info.n_of_philos;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			philo = philos[i];
			pthread_mutex_lock(&table->death_mutex);
			if (get_timestamp(philo->last_eating_time) >= info.t_to_die)
			{
				table->is_dead = 1;
				print_msg(table, get_timestamp(table->start_time), philo->id, DIED);
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_mutex);
			i++;
		}	
	}
	return (NULL);
}
