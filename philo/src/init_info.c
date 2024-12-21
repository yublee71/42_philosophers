/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:13:34 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 23:14:05 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	valid_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (valid_input(argv) < 0)
		return (-1);
	info->n_of_philos = ft_atoi(argv[1]);
	info->t_to_die = (unsigned long)ft_atoi(argv[2]); //TODO: compare with other values, in case of 0?
	info->t_to_eat = (unsigned long)ft_atoi(argv[3]);
	info->t_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		info->n_of_times_to_eat = ft_atoi(argv[5]); //TODO: in case of 0?
	else
		info->n_of_times_to_eat = 0;
	return (0);
}
