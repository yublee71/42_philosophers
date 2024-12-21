/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:51:45 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 17:54:05 by yublee           ###   ########.fr       */
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
	pthread_t		time_logger_th;
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

typedef enum e_action
{
	DIED = 0,
	THINKING = 1,
	FORK = 2,
	EATING = 3,
	SLEEPING = 4,
}	t_action;

int		init_table(t_table *table, t_info info);
void	*philosopher(void *arg);
void	*timelogger(void *arg);
void	free_table(t_table *table);

// //utils
int				ft_atoi(const char *nptr);
unsigned long	get_timestamp(unsigned long start_time);
unsigned long	get_current_time_in_ms(void);

#endif