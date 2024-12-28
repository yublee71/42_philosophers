/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/22 21:25 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	pick_up_forks(int id, int t_num, t_table *table)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&table->forks_mutex[id]);
		table->forks[id] = 1;
		print_msg(table, id, FORK);
		if (t_num == 1)
		{
			pthread_mutex_unlock(&table->forks_mutex[id]);
			return (-1);
		}
		pthread_mutex_lock(&table->forks_mutex[(id + 1) % t_num]);
		table->forks[(id + 1) % t_num] = 1;
		print_msg(table, id, FORK);
	}
	else
	{
		pthread_mutex_lock(&table->forks_mutex[(id + 1) % t_num]);
		table->forks[(id + 1) % t_num] = 1;
		print_msg(table, id, FORK);
		pthread_mutex_lock(&table->forks_mutex[id]);
		table->forks[id] = 1;
		print_msg(table, id, FORK);
	}
	return (0);
}

static void	put_down_forks(int id, int t_num, t_table *table)
{
	if (id % 2 == 0)
	{
		table->forks[id] = 0;
		pthread_mutex_unlock(&table->forks_mutex[id]);
		table->forks[(id + 1) % t_num] = 0;
		pthread_mutex_unlock(&table->forks_mutex[(id + 1) % t_num]);
	}
	else
	{
		table->forks[(id + 1) % t_num] = 0;
		pthread_mutex_unlock(&table->forks_mutex[(id + 1) % t_num]);
		table->forks[id] = 0;
		pthread_mutex_unlock(&table->forks_mutex[id]);
	}
}

static int	eat_philo(int id, unsigned long t, t_table *table, t_philo *philo)
{
	int	total_num;

	total_num = table->info.n_of_philos;
	if (pick_up_forks(id, total_num, table) < 0)
		return (-1);
	if (is_table_active(table))
	{
		pthread_mutex_lock(&table->death_mutex);
		philo->last_eating_time = get_current_time_in_ms();
		pthread_mutex_unlock(&table->death_mutex);
		print_msg(table, id, EATING);
		pthread_mutex_lock(&table->death_mutex);
		philo->n_of_eating++;
		pthread_mutex_unlock(&table->death_mutex);
		optimized_usleep(t);
	}
	put_down_forks(id, total_num, table);
	return (0);
}

static void	sleep_philo(int id, unsigned long t, t_table *table)
{
	print_msg(table, id, SLEEPING);
	optimized_usleep(t);
}

void	*philosopher(void *arg)
{
	t_philo			*philo;
	t_table			*table;
	int				id;
	t_info			info;

	philo = (t_philo *)arg;
	table = philo->table;
	id = philo->id;
	info = table->info;
	while (is_table_active(table))
	{
		if (is_table_active(table))
			print_msg(table, id, THINKING);
		if (is_table_active(table))
		{
			if (id % 2 == 0)
				usleep(1000);
			if (eat_philo(id, info.t_to_eat, table, philo) < 0)
				break ;
		}
		if (is_table_active(table))
			sleep_philo(id, info.t_to_sleep, table);
	}
	return (NULL);
}
