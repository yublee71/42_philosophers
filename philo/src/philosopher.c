/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 17:08:29 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philosopher(t_table *table)
{
	unsigned long	s_time;
	t_philo			**philos;
	int				i;
	int				n;
	
	s_time = get_current_time_in_ms();
	table->start_time = s_time;
	philos = table->philos;
	n = table->info.n_of_philos;
	i = 0;
	while (i < n)
	{
		philos[i]->last_eating_time = s_time;
		pthread_create(&philos[i]->philo_th, NULL, &routine, (void *)philos[i]); //TODO: error check;
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(philos[i]->philo_th, NULL);
		i++;
	}
}