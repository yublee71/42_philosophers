/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:02:58 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 14:28:18 by yublee           ###   ########.fr       */
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

// void	free_array(void **arr, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 		free(arr[i++]);
// 	free(arr);
// }

// unsigned long	get_timestamp(unsigned long start_time)
// {
// 	struct timeval	tv;

// 	if (!start_time)
// 		return (0);
// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time);
// }

// unsigned long	get_realtimestamp(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }