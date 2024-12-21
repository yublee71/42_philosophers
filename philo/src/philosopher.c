/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/22 00:43:50 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	pick_up_forks(int id, int t_num, unsigned long t, t_table *table)
{
	if (id % 2 == 0)
	{
		usleep(t * 10);
		pthread_mutex_lock(&table->forks_mutex[id]);
		table->forks[id] = 1;
		print_msg(table, get_timestamp(table->start), id, FORK);
		if (t_num == 1)
		{
			pthread_mutex_unlock(&table->forks_mutex[id]);
			return (-1);
		}
		pthread_mutex_lock(&table->forks_mutex[(id + 1) % t_num]);
		table->forks[(id + 1) % t_num] = 1;
		print_msg(table, get_timestamp(table->start), id, FORK);
	}
	else
	{
		pthread_mutex_lock(&table->forks_mutex[(id + 1) % t_num]);
		table->forks[(id + 1) % t_num] = 1;
		print_msg(table, get_timestamp(table->start), id, FORK);
		pthread_mutex_lock(&table->forks_mutex[id]);
		table->forks[id] = 1;
		print_msg(table, get_timestamp(table->start), id, FORK);
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
	unsigned long	s_time;
	int				total_num;

	s_time = table->start;
	total_num = table->info.n_of_philos;
	if (pick_up_forks(id, total_num, t, table) < 0)
		return (-1);
	if (is_table_active(table))
	{
		pthread_mutex_lock(&table->death_mutex);
		philo->last_eating_time = get_current_time_in_ms();
		pthread_mutex_unlock(&table->death_mutex);
		print_msg(table, get_timestamp(s_time), id, EATING);
		pthread_mutex_lock(&table->death_mutex);
		philo->n_of_eating++;
		pthread_mutex_unlock(&table->death_mutex);
		usleep(t * 1000);
	}
	put_down_forks(id, total_num, table);
	return (0);
}

static void	sleep_philo(int id, unsigned long t, t_table *table)
{
	unsigned long	s_time;

	s_time = table->start;
	print_msg(table, get_timestamp(s_time), id, SLEEPING);
	usleep(t * 1000);
}

void	*philosopher(void *arg)
{
	t_philo			*philo;
	t_table			*table;
	int				id;
	unsigned long	s_time;
	t_info			info;

	philo = (t_philo *)arg;
	table = philo->table;
	id = philo->id;
	s_time = table->start;
	info = table->info;
	while (is_table_active(table))
	{
		if (is_table_active(table))
			print_msg(table, get_timestamp(s_time), id, THINKING);
		if (is_table_active(table))
		{
			if (eat_philo(id, info.t_to_eat, table, philo) < 0)
				break ;
		}
		if (is_table_active(table))
			sleep_philo(id, info.t_to_sleep, table);
	}
	return (NULL);
}
