/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:15:47 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 23:16:47 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	cleanup_table_simulation(t_table *table)
{
	t_philo			**philos;
	pthread_mutex_t	*forks_mutex;
	int				i;
	int				n;
	
	philos = table->philos;
	forks_mutex = table->forks_mutex;
	n = table->info.n_of_philos;
	i = 0;
	while (i < n)
		pthread_join(philos[i++]->philo_th, NULL);
	pthread_join(table->timelogger_th, NULL);
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&forks_mutex[i++]);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free_table(table);
}

void	start_table_simulation(t_table *table)
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
		pthread_create(&philos[i]->philo_th, NULL, &philosopher, (void *)philos[i]); //TODO: error check;
		i++;
	}
	pthread_create(&table->timelogger_th, NULL, &timelogger, (void *)table); //TODO: error check;
}
