/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:38:55 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 17:22:45 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
		printf("%lu %d is thinking\n", get_timestamp(s_time), p_num);
		if (p_num % 2 == 0)
		{
			pthread_mutex_lock(&forks_mutex[p_num]);
			forks[p_num] = 1;
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
			if (p_num == (p_num + 1) % total_num)
				break ;
			pthread_mutex_lock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 1;
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
		}
		else
		{
			usleep(info.t_to_eat * 10);
			pthread_mutex_lock(&forks_mutex[(p_num + 1) % total_num]);
			forks[(p_num + 1) % total_num] = 1;
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
			pthread_mutex_lock(&forks_mutex[p_num]);
			forks[p_num] = 1;
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
		}
		philo->last_eating_time = get_current_time_in_ms();
		printf("%lu %d is eating\n", get_timestamp(s_time), p_num);
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
		printf("%lu %d is sleeping\n", get_timestamp(s_time), p_num);
		usleep(info.t_to_sleep * 1000);
	}
	return (NULL);
}
