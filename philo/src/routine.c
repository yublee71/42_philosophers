/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:32:46 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 23:47:05 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// void	*time_logger(void *arg)
// {
// 	t_thread_info	**th_info_arg;
// 	t_thread_info	*th_info;
// 	t_info			info;
// 	int				i;
// 	int				n_of_philos;

// 	th_info_arg = (t_thread_info **)arg;
// 	th_info = th_info_arg[0];
// 	info = th_info->info;
// 	n_of_philos = info.n_of_philos;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < n_of_philos)
// 		{
// 			th_info = th_info_arg[i];
// 			if (!th_info->lock_acquired
// 				&& get_timestamp(th_info->start_starving_time) >= info.t_to_die)
// 			{
// 				printf("%lu %d died\n", get_timestamp(th_info->start_time), th_info->philo_num);
// 				return (NULL);
// 			}
// 			i++;
// 		}	
// 	}

// }

void	*routine(void *arg)
{
	t_thread_info	*th_info;
	t_info			info;
	pthread_mutex_t	**forks;
	int				p_num;
	unsigned long	s_time;
	int				total_num;

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
		th_info->start_starving_time = get_realtimestamp();
		printf("%lu %d is thinking\n", get_timestamp(s_time), p_num);
		if (p_num % 2 == 0)
		{
			pthread_mutex_lock(forks[p_num]);
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
			pthread_mutex_lock(forks[(p_num + 1) % total_num]);
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
		}
		//3 -> 0: 0,2 / 2: 2,1
		//4 -> 0: 0,3 / 2: 2,1
		//5 -> 0: 0,4 / 2: 2,1 / 4: 4,3
		//6 -> 0: 0,5 / 2: 2,1 / 4: 4,3
		else
		{
			usleep(info.t_to_eat * 100);
			pthread_mutex_lock(forks[(p_num + 1) % total_num]);
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
			pthread_mutex_lock(forks[p_num]);
			printf("%lu %d has taken a fork\n", get_timestamp(s_time), p_num);
		}
		// - timestamp_in_ms X has taken a fork
		// - timestamp_in_ms X is eating
		// - timestamp_in_ms X is sleeping
		// - timestamp_in_ms X is thinking
		// - timestamp_in_ms X died
		th_info->lock_acquired = 1;
		th_info->start_starving_time = 0;
		printf("%lu %d is eating\n", get_timestamp(s_time), p_num);
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
		th_info->lock_acquired = 0;
		th_info->start_starving_time = get_realtimestamp();
		printf("%lu %d is sleeping\n", get_timestamp(s_time), p_num);
		usleep(info.t_to_sleep * 1000);
	}
	return (NULL);
}