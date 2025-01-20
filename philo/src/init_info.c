/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:13:34 by yublee            #+#    #+#             */
/*   Updated: 2025/01/20 18:24:38 by yublee           ###   ########.fr       */
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
		return (err_msg(STR_ERR_ARG_COUNT, -1));
	if (valid_input(argv) < 0)
		return (err_msg(STR_ERR_ARG_VALUE, -1));
	info->n_of_philos = ft_atoi(argv[1]);
	info->t_to_die = (unsigned long)ft_atoi(argv[2]);
	info->t_to_eat = (unsigned long)ft_atoi(argv[3]);
	info->t_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (!info->n_of_philos || !info->t_to_die
		|| !info->t_to_eat || !info->t_to_sleep)
		return (err_msg(STR_ERR_ARG_VALUE, -1));
	if (argc == 6)
	{
		info->n_of_times_to_eat = ft_atoi(argv[5]);
		if (info->n_of_times_to_eat == 0)
			return (err_msg(STR_ERR_ARG_VALUE, -1));
	}
	else
		info->n_of_times_to_eat = 0;
	return (0);
}
