/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:35:27 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 13:49:54 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	set_forks_mutex(int n_of_philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		table->forks_mutex[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!table->forks_mutex[i])
		{
			free_array((void **)table->forks_mutex, i - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	set_philos(int n_of_philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		table->philos[i] = (pthread_t *)malloc(sizeof(pthread_t));//TODO: test with malloc fail
		if (!table->philos[i])
		{
			free_array((void **)table->philos, i - 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	set_thread_infos(t_info info, t_table *table)
{
	int				i;
	const int		n_of_philos = info.n_of_philos;
	t_thread_info	*th_info;
	unsigned long	start_time;

	start_time = get_realtimestamp();
	i = 0;
	while (i < n_of_philos)
	{
		th_info = (t_thread_info *)malloc(sizeof(t_thread_info));//TODO: test with malloc fail
		if (!th_info)
		{
			free_array((void **)table->th_info_arr, i - 1);
			return (-1);
		}
		th_info->info = info;
		th_info->forks_mutex = table->forks_mutex;
		th_info->forks = table->forks;
		th_info->philo_num = i;
		th_info->start_time = start_time;
		th_info->start_starving_time = start_time;
		th_info->lock_acquired = 0;
		th_info->is_done = table->is_done;
		th_info->time_mutex = table->time_mutex;
		table->th_info_arr[i] = th_info;
		i++;
	}
	return (0);
}

t_table	*set_table(t_info info)
{
	t_table	*table;
	int		n_of_philos;
	int		i;

	n_of_philos = info.n_of_philos;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philos = (pthread_t **)malloc(sizeof(pthread_t *) * n_of_philos);
	table->forks_mutex = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * n_of_philos);
	table->time_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	table->th_info_arr = (t_thread_info **)malloc(sizeof(t_thread_info *) * n_of_philos);
	table->is_done = (int *)malloc(sizeof(int));
	table->forks = (int *)malloc(sizeof(int) * n_of_philos);
	if (!table->philos || !table->forks_mutex || !table->th_info_arr || !table->is_done || !table->forks || !table->time_mutex)
		return (NULL);
	*(table->is_done) = 0;
	i = 0;
	while (i < n_of_philos)
		table->forks[i++] = 0;
	if (set_forks_mutex(n_of_philos, table) < 0
		|| set_philos(n_of_philos, table) < 0
		|| set_thread_infos(info, table) < 0)
		return (NULL);
	return (table);
}

