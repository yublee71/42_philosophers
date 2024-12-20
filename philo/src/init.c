/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:16:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 20:00:04 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_table(t_table *table, int n_of_philos)
{
	int				i;

	i = 0;
	while (i < n_of_philos)
		pthread_mutex_init(table->forks[i++], NULL);
	i = 0;
	while (i < n_of_philos)
	{
		pthread_create(table->philos[i], NULL, &routine, (void *)table->th_info_arr[i]);
		i++;
	}
}
