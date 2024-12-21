/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:53:49 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 14:34:34 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
	// start_table(table);
	// cleanup_table(table, n_of_philos);
	return (0);
}