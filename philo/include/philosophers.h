/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:51:45 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 16:57:41 by yublee           ###   ########.fr       */
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

typedef struct s_table
{
	t_info			info;
	int				*forks; //malloc
	struct s_philo	**philos; //malloc
	int				is_dead;
	pthread_mutex_t	*forks_mutex; //malloc
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	unsigned long	start_time;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_th;
	int				philo_num;
	unsigned long	last_eating_time;
}	t_philo;

int		init_table(t_table *table, t_info info);
void	philosopher(t_table *table);
void	*routine(void *arg);
// void	*time_logger(void *arg);
// void	cleanup_table(t_table *table, int n_of_philos);
void	free_table(t_table *table);

// //utils
int				ft_atoi(const char *nptr);
unsigned long	get_timestamp(unsigned long start_time);
unsigned long	get_current_time_in_ms(void);

#endif