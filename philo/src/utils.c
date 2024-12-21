/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:02:58 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 18:27:08 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *nptr)
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

unsigned long	get_timestamp(unsigned long start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
}

unsigned long	get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_msg(t_table *table, unsigned long time, int id, t_action a)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%lu ", time);
	printf("%d ", id);
	if (a == DIED)
		printf("%s", "died\n");
	else if (a == THINKING)
		printf("%s", "is thinking\n");
	else if (a == FORK)
		printf("%s", "has taken a fork\n");
	else if (a == EATING)
		printf("%s", "is eating\n");
	else if (a == SLEEPING)
		printf("%s", "is sleeping\n");
	pthread_mutex_unlock(&table->print_mutex);
}
