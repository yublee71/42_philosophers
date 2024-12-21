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

static void	print_msg(t_table *table, unsigned long time, int id, t_action a)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu ", time);
	printf("%d ", id);
	if (a == DIED)
		printf("%s", "died\n");
	else if (a == THINKING)
		printf("%s", "is thinking\n");
	else if (a == FORK)
		printf("%s", "has taken a fork\n");
	else if (a == EATING)
		printf("%s", "is eating\n");
	else if (a == SLEEPING)
		printf("%s", "is sleeping\n");
	pthread_mutex_unlock(&table->print_mutex);
}

static void	eat_philo(int id, unsigned long t, t_table *table, t_philo *philo)
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
		if (id == (id + 1) % total_num)
			return ;//TODO: modify
		pthread_mutex_lock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
	}
	else
	{
		usleep(t * 20);
		pthread_mutex_lock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
		pthread_mutex_lock(&forks_mutex[id]);
		forks[id] = 1;
		print_msg(table, get_timestamp(s_time), id, FORK);
	}
	philo->last_eating_time = get_current_time_in_ms();
	print_msg(table, get_timestamp(s_time), id, EATING);
	usleep(t * 1000);
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&forks_mutex[id]);
		forks[id] = 0;
		pthread_mutex_unlock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 0;
	}
	else
	{
		pthread_mutex_unlock(&forks_mutex[(id + 1) % total_num]);
		forks[(id + 1) % total_num] = 0;
		pthread_mutex_unlock(&forks_mutex[id]);
		forks[id] = 0;
	}
}

static void	sleep_philo(int id, unsigned long t_to_sleep, t_table *table)
{
	unsigned long	s_time;

	s_time = table->start_time;
	print_msg(table, get_timestamp(s_time), id, SLEEPING);
	usleep(t_to_sleep * 1000);
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
	while (1)
	{
		print_msg(table, get_timestamp(s_time), id, THINKING);
		eat_philo(id, info.t_to_eat, table, philo);
		sleep_philo(id, info.t_to_sleep, table);
	}
	return (NULL);
}
