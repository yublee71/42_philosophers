/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timelogger.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:23 by yublee            #+#    #+#             */
/*   Updated: 2024/12/22 18:23:07 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*timelogger(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *)arg;
	while (is_table_active(table))
	{
		i = 0;
		while (i < table->info.n_of_philos)
		{
			philo = table->philos[i++];
			pthread_mutex_lock(&table->death_mutex);
			if (get_timestamp(philo->last_eating_time) >= table->info.t_to_die)
			{
				table->is_dead = 1;
				print_msg(table, philo->id, DIED);
				pthread_mutex_unlock(&table->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->death_mutex);
		}
		usleep(100);
	}
	return (NULL);
}
