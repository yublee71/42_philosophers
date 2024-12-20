/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:51:45 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 23:47:09 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_info
{
	int				n_of_philos;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	unsigned long	n_of_times_to_eat;
}	t_info;

typedef struct s_thread_info
{
	t_info			info;
	pthread_mutex_t	**forks;
	int				philo_num;
	unsigned long	start_time;
	unsigned long	start_starving_time;
	int				lock_acquired;
}	t_thread_info;

typedef struct s_table
{
	pthread_t		**philos;
	pthread_mutex_t	**forks;
	t_thread_info	**th_info_arr;
}	t_table;

t_info	set_info(int argc, char **argv);
t_table	*set_table(t_info info);

void	init_table(t_table *table, int n_of_philos);
void	*routine(void *arg);
// void	*time_logger(void *arg);
void	cleanup_table(t_table *table, int n_of_philos);

//utils
int				ft_atoi(const char *nptr);
void			free_array(void **arr, int size);
unsigned long	get_timestamp(unsigned long start_time);
unsigned long	get_realtimestamp(void);

#endif