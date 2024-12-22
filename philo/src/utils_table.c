/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 22:06:53 by yublee            #+#    #+#             */
/*   Updated: 2024/12/22 18:28:08 by yublee           ###   ########.fr       */
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

void	print_msg(t_table *table, int id, t_action a)
{
	if (a == DIED)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%lu ", get_timestamp(table->start));
		printf("%d ", id + 1);
		printf("%s", "died\n");
		pthread_mutex_unlock(&table->print_mutex);
	}
	else if (is_table_active(table))
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%lu ", get_timestamp(table->start));
		printf("%d ", id + 1);
		if (a == THINKING)
			printf("%s", "is thinking\n");
		else if (a == FORK)
			printf("%s", "has taken a fork\n");
		else if (a == EATING)
			printf("%s", "is eating\n");
		else if (a == SLEEPING)
			printf("%s", "is sleeping\n");
		pthread_mutex_unlock(&table->print_mutex);
	}
}

static int	is_anyone_dead(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->is_dead)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

int	is_everyone_full(t_table *table)
{
	int		i;
	int		n;
	t_philo	**philos;

	i = 0;
	n = table->info.n_of_philos;
	philos = table->philos;
	pthread_mutex_lock(&table->death_mutex);
	while (i < n && table->info.n_of_times_to_eat)
	{
		if (philos[i]->n_of_eating < table->info.n_of_times_to_eat)
			break ;
		i++;
	}
	pthread_mutex_unlock(&table->death_mutex);
	if (i == n)
		return (1);
	return (0);
}

int	is_table_active(t_table *table)
{
	if (is_everyone_full(table) || is_anyone_dead(table))
		return (0);
	return (1);
}
