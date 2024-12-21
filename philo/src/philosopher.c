/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 17:56:45 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	print_msg(t_table *table, unsigned long time, int p_num, t_action a)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu ", time);
	printf("%d ", p_num);
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

void	*philosopher(void *arg)
{
	t_philo			*philo;
	int				p_num;
	t_table			*table;
	unsigned long	s_time;
	int				*forks;
	pthread_mutex_t	*forks_mutex;
	t_info			info;
	int				total_num;

	philo = (t_philo *)arg;
	p_num = philo->philo_num;
	table = philo->table;
	s_time = table->start_time;
	forks_mutex = table->forks_mutex;
	forks = table->forks;
	info = table->info;
	total_num = info.n_of_philos;
	while (1)
	{
		print_msg(table, get_timestamp(s_time), p_num, THINKING);
		if (p_num % 2 == 0)
		{
			pthread_mutex_lock(&forks_mutex[p_num]);
			forks[p_num] = 1;
			print_msg(table, get_timestamp(s_time), p_num, FORK);
			if (p_num == (p_num + 1) % total_num)
				break ;
			pthread_mutex_lock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 1;
			print_msg(table, get_timestamp(s_time), p_num, FORK);
		}
		else
		{
			usleep(info.t_to_eat * 10);
			pthread_mutex_lock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 1;
			print_msg(table, get_timestamp(s_time), p_num, FORK);
			pthread_mutex_lock(&forks_mutex[p_num]);
			forks[p_num] = 1;
			print_msg(table, get_timestamp(s_time), p_num, FORK);
		}
		philo->last_eating_time = get_current_time_in_ms();
		print_msg(table, get_timestamp(s_time), p_num, EATING);
		usleep(info.t_to_eat * 1000);
		if (p_num % 2 == 0)
		{
			pthread_mutex_unlock(&forks_mutex[p_num]);
			forks[p_num] = 0;
			pthread_mutex_unlock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 0;
		}
		else
		{
			pthread_mutex_unlock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 0;
			pthread_mutex_unlock(&forks_mutex[p_num]);
			forks[p_num] = 0;
		}
		print_msg(table, get_timestamp(s_time), p_num, SLEEPING);
		usleep(info.t_to_sleep * 1000);
	}
	return (NULL);
}
