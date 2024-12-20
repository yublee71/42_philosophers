/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:32:46 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 23:15:38 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_thread_info	*th_info;
	t_info			info;
	pthread_mutex_t	**forks;
	int				p_num;
	unsigned long	s_time;
	int				total_num;
	unsigned long	start_starving_time;


	th_info = (t_thread_info *)arg;
	info = th_info->info;
	forks = th_info->forks;
	p_num = th_info->philo_num;
	s_time = th_info->start_time;
	total_num = info.n_of_philos;
	// printf("num of times to eat: %d\n", info.n_of_times_to_eat);
	// printf("time to die: %d\n", info.t_to_die);
	// printf("time to eat: %d\n", info.t_to_eat);
	// printf("time to sleep: %d\n", info.t_to_sleep);
	// printf("p_num: %d\n", p_num);
	// printf("total_num: %d\n", total_num);
	// printf("s_time: %lu\n", s_time);
	while (1)
	{
		start_starving_time = get_timestamp() - s_time;
		printf("%lu %d is thinking\n", start_starving_time, p_num);
		if (p_num % 2 == 0)
		{
			pthread_mutex_lock(forks[p_num]);
			printf("%lu %d has taken a fork\n", get_timestamp() - s_time, p_num);
			pthread_mutex_lock(forks[(p_num + 1) % total_num]);
			printf("%lu %d has taken a fork\n", get_timestamp() - s_time, p_num);
		}
		//3 -> 0: 0,2 / 2: 2,1
		//4 -> 0: 0,3 / 2: 2,1
		//5 -> 0: 0,4 / 2: 2,1 / 4: 4,3
		//6 -> 0: 0,5 / 2: 2,1 / 4: 4,3
		else
		{
			usleep(info.t_to_eat * 100);
			pthread_mutex_lock(forks[(p_num + 1) % total_num]);
			printf("%lu %d has taken a fork\n", get_timestamp() - s_time, p_num);
			pthread_mutex_lock(forks[p_num]);
			printf("%lu %d has taken a fork\n", get_timestamp() - s_time, p_num);
		}
		// - timestamp_in_ms X has taken a fork
		// - timestamp_in_ms X is eating
		// - timestamp_in_ms X is sleeping
		// - timestamp_in_ms X is thinking
		// - timestamp_in_ms X died
		printf("%lu %d is eating\n", get_timestamp() - s_time, p_num);
		usleep(info.t_to_eat * 1000);
		if (p_num % 2 == 0)
		{
			pthread_mutex_unlock(forks[p_num]);
			pthread_mutex_unlock(forks[(p_num + 1) % total_num]);
		}
		else
		{
			pthread_mutex_unlock(forks[(p_num + 1) % total_num]);
			pthread_mutex_unlock(forks[p_num]);
		}
		printf("%lu %d is sleeping\n", get_timestamp() - s_time, p_num);
		usleep(info.t_to_sleep * 1000);
	}
	return (NULL);
}