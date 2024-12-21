/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:40:06 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 12:36:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	cleanup_table(t_table *table, int n_of_philos)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		if (table->forks[i] == 1)
			pthread_mutex_unlock(table->forks_mutex[i]);
		pthread_mutex_destroy(table->forks_mutex[i]);
		free(table->forks_mutex[i++]);
	}
	pthread_mutex_destroy(table->time_mutex);
	i = 0;
	while (i < n_of_philos)
	{
		pthread_detach(*(table->philos[i]));
		free(table->philos[i++]);
	}
	i = 0;
	while (i < n_of_philos)
		free(table->th_info_arr[i++]);
	free(table->philos);
	free(table->forks_mutex);
	free(table->th_info_arr);
	free(table);
}