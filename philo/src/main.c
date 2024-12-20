/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:53:49 by yublee            #+#    #+#             */
/*   Updated: 2024/12/20 20:04:20 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_info			info;
	t_table			*table;
	int				n_of_philos;

	if (argc == 5 || argc == 6)
	{
		info = set_info(argc, argv);
		table = set_table(info);
		if (!table)
			return (1);
		n_of_philos = info.n_of_philos;
		init_table(table, n_of_philos);
		cleanup_table(table, n_of_philos);
	}
	return (1);
}