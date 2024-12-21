/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:53:49 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 14:34:34by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	cleanup_table(t_table *table)
{
	t_philo			**philos;
	pthread_mutex_t	*forks_mutex;
	int				i;
	int				n;
	
	philos = table->philos;
	forks_mutex = table->forks_mutex;
	n = table->info.n_of_philos;
	i = 0;
	while (i < n)
		pthread_join(philos[i++]->philo_th, NULL);
	pthread_join(table->timelogger_th, NULL);
	i = 0;
	while (i < n)
		pthread_mutex_destroy(&forks_mutex[i++]);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free_table(table);
}

static void	start_table(t_table *table)
{
	unsigned long	s_time;
	t_philo			**philos;
	int				i;
	int				n;
	
	s_time = get_current_time_in_ms();
	table->start_time = s_time;
	philos = table->philos;
	n = table->info.n_of_philos;
	i = 0;
	while (i < n)
	{
		philos[i]->last_eating_time = s_time;
		pthread_create(&philos[i]->philo_th, NULL, &philosopher, (void *)philos[i]); //TODO: error check;
		i++;
	}
	pthread_create(&table->timelogger_th, NULL, &timelogger, (void *)table); //TODO: error check;
}

static int	get_info(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (-1);
	info->n_of_philos = ft_atoi(argv[1]); // TODO: check valid input
	info->t_to_die = (unsigned long)ft_atoi(argv[2]); //TODO: compare with other values, in case of 0?
	info->t_to_eat = (unsigned long)ft_atoi(argv[3]);
	info->t_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		info->n_of_times_to_eat = (unsigned long)ft_atoi(argv[5]);
	else
		info->n_of_times_to_eat = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_info			info;
	t_table			table;

	if (get_info(argc, argv, &info) < 0)
		return (1);
	if (init_table(&table, info) < 0)
		return (1);
	start_table(&table);
	cleanup_table(&table);
	return (0);
}