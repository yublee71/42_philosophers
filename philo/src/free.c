/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:40:06 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 21:29:15 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_table(t_table *table)
{
	int	i;
	int	n;

	if (table->forks)
		free(table->forks);
	if (table->forks_mutex)
		free(table->forks_mutex);
	if (table->philos)
	{
		i = 0;
		n = table->info.n_of_philos;
		while (i < n)
		{
			if (table->philos[i])
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
}
