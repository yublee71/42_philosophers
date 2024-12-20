/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:35:27 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 23:36:36 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	set_forks(int n_of_philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		table->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!table->forks[i])
		{
			free_array((void **)table->forks, i - 1);
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
		th_info->forks = table->forks;
		th_info->philo_num = i;
		th_info->start_time = start_time;
		th_info->start_starving_time = 0;
		th_info->lock_acquired = 0;
		table->th_info_arr[i] = th_info;
		i++;
	}
	return (0);
}

t_table	*set_table(t_info info)
{
	t_table	*table;
	int		n_of_philos;

	n_of_philos = info.n_of_philos;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->philos = (pthread_t **)malloc(sizeof(pthread_t *) * n_of_philos);
	table->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * n_of_philos);
	table->th_info_arr = (t_thread_info **)malloc(sizeof(t_thread_info *) * n_of_philos);
	if (!table->philos || !table->forks || !table->th_info_arr)
		return (NULL);
	if (set_forks(n_of_philos, table) < 0
		|| set_philos(n_of_philos, table) < 0
		|| set_thread_infos(info, table) < 0)
		return (NULL);
	return (table);
}

t_info	set_info(int argc, char **argv)
{
	t_info	info;

	info.n_of_philos = ft_atoi(argv[1]);
	info.t_to_die = (unsigned long)ft_atoi(argv[2]); //TODO: compare with other values, in case of 0?
	info.t_to_eat = (unsigned long)ft_atoi(argv[3]);
	info.t_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		info.n_of_times_to_eat = (unsigned long)ft_atoi(argv[5]);
	else
		info.n_of_times_to_eat = 0;
	return (info);
}