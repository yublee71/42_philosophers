/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:52:30 by yublee            #+#    #+#             */
/*   Updated: 2024/07/26 23:40:20 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Your(s) program(s) should take the following arguments:
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
// ◦ number_of_philosophers: The number of philosophers and also the number
// of forks.
// ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
// milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
// ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
// During that time, they will need to hold two forks.
// ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
// ◦ number_of_times_each_philosopher_must_eat (optional argument): If all
// philosophers have eaten at least number_of_times_each_philosopher_must_eat
// times, the simulation stops. If not specified, the simulation stops when a
// philosopher dies.


// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock


#include "philosophers.h"

typedef struct arg_s
{
	int	forks;
	int	philos;
}	arg_t;

void	*start_routine(void *args)
{
	printf("%d has taken a fork\n", ((arg_t *)args)->philos);
	printf("%d fork is left\n", ((arg_t *)args)->forks);
	// sleep(1);
	// pthread_mutex_unlock(&mutex);
	free(args);
	return (NULL);
}

static int	ft_atoi(const char *nptr)
{
	int	nbr;
	int	minus;

	nbr = 0;
	minus = 1;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			minus *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	return (minus * nbr);
}

int	main(int argc, char *argv[])
{
	int	given_forks;
	int	given_num;
	int	status;
	int	i;
	pthread_mutex_t mutex;

	if (argc != 5 && argc != 6)
		return (1);
	given_forks = ft_atoi(argv[1]);
	given_num = given_forks;

	pthread_t thread[given_forks];
	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < given_num)
	{
		pthread_mutex_lock(&mutex);
		arg_t *args = malloc(sizeof(arg_t *));
		args->philos = i;
		args->forks = given_forks;
		// *arg = i;
		pthread_create(&thread[args->philos], NULL, start_routine, args);
		i++;
		if (given_forks >= 2)
		{
			given_forks--;
			given_forks--;
		}
		if (given_forks <= 0)
			break ;
		pthread_mutex_unlock(&mutex);
	}
	i = 0;
	while (i < given_num)
		pthread_join(thread[i++], (void **)&status);
	pthread_mutex_destroy(&mutex);
}