/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 18:10:26by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


static int	eat_philo(int id, unsigned long t, t_table *table, t_philo *philo)
{
	int				*forks;
	pthread_mutex_t	*forks_mutex;
	unsigned long	s_time;
	int				total_num;

	forks_mutex = table->forks_mutex;
	forks = table->forks;
	s_time = table->start_time;
	total_num = table->info.n_of_philos;
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&forks_mutex[id]);
		forks[id] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
		if (total_num == 1)
		{
			pthread_mutex_unlock(&forks_mutex[id]);
			return (-1);
		}
		pthread_mutex_lock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
	}
	else
	{
		usleep(t * 10);
		pthread_mutex_lock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
		pthread_mutex_lock(&forks_mutex[id]);
		forks[id] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
	}
	pthread_mutex_lock(&table->death_mutex);
	philo->last_eating_time = get_current_time_in_ms();
	pthread_mutex_unlock(&table->death_mutex);
	print_msg(table, get_timestamp(s_time), id, EATING);
	usleep(t * 1000);
	if (id % 2 == 0)
	{
		forks[id] = 0;
		pthread_mutex_unlock(&forks_mutex[id]);
		forks[(id + 1) % total_num] = 0;
		pthread_mutex_unlock(&forks_mutex[(id + 1) % total_num]);
	}
	else
	{
		forks[(id + 1) % total_num] = 0;
		pthread_mutex_unlock(&forks_mutex[(id + 1) % total_num]);
		forks[id] = 0;
		pthread_mutex_unlock(&forks_mutex[id]);
	}
	return (0);
}

static void	sleep_philo(int id, unsigned long t, t_table *table)
{
	unsigned long	s_time;

	s_time = table->start_time;
	print_msg(table, get_timestamp(s_time), id, SLEEPING);
	usleep(t * 1000);
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
	s_time = table->start_time;
	info = table->info;
	while (!is_anyone_dead(table))
	{
		print_msg(table, get_timestamp(s_time), id, THINKING);
		if (eat_philo(id, info.t_to_eat, table, philo) < 0)
			break ;
		sleep_philo(id, info.t_to_sleep, table);
	}
	return (NULL);
}
