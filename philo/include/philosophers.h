/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:51:45 by yublee            #+#    #+#             */
/*   Updated: 2024/12/28 13:15:07 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define STR_ERR_INPUT		"Error: Invalid input.\n"
# define STR_ERR_ARG_COUNT	"Error: Invalid number of arguments.\n"
# define STR_ERR_ARG_VALUE	"Error: Invalid argument value.\n"
# define STR_ERR_MALLOC		"Error: Could not allocate memory.\n"
# define STR_ERR_THREAD		"Error: Could not create thread.\n"
# define STR_ERR_MUTEX		"Error: Could not create mutex.\n"

typedef struct s_info
{
	int				n_of_philos;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	int				n_of_times_to_eat;
}	t_info;

typedef struct s_table
{
	t_info			info;
	int				*forks;
	struct s_philo	**philos;
	int				is_dead;
	pthread_t		timelogger_th;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	unsigned long	start;
}	t_table;

typedef struct s_philo
{
	t_table			*table;
	pthread_t		philo_th;
	int				id;
	unsigned long	last_eating_time;
	int				n_of_eating;
}	t_philo;

typedef enum e_action
{
	DIED = 0,
	THINKING = 1,
	FORK = 2,
	EATING = 3,
	SLEEPING = 4,
}	t_action;

//initiation
int				init_info(int argc, char **argv, t_info *info);
int				init_table(t_table *table, t_info info);

//simulation
int				start_table_simulation(t_table *table);
void			cleanup_table_simulation(t_table *table);

//thread routine functions
void			*philosopher(void *arg);
void			*timelogger(void *arg);

//table utils
void			free_table(t_table *table);
void			print_msg(t_table *table, int id, t_action a);
int				is_table_active(t_table *table);
int				is_everyone_full(t_table *table);

//utils
int				err_msg(char *msg, int return_val);
void			optimized_usleep(unsigned long t);
int				ft_atoi(const char *nptr);
unsigned long	get_timestamp(unsigned long start);
unsigned long	get_current_time_in_ms(void);

#endif