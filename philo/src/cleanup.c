/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:40:06 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 20:05:31 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	cleanup_table(t_table *table, int n_of_philos)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		pthread_join(*(table->philos[i]), NULL);
		free(table->philos[i++]);
	}
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(table->forks[i]);
		free(table->forks[i++]);
	}
	i = 0;
	while (i < n_of_philos)
		free(table->th_info_arr[i++]);
	free(table->philos);
	free(table->forks);
	free(table->th_info_arr);
	free(table);
}