/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:53:49 by yublee            #+#    #+#             */
/*   Updated: 2025/01/19 14:46:02 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_table	table;

	if (init_info(argc, argv, &info) < 0)
		return (EXIT_FAILURE);
	if (init_table(&table, info) < 0
		|| start_table_simulation(&table) < 0)
	{
		free_table(&table);
		return (EXIT_FAILURE);
	}
	cleanup_table_simulation(&table);
	return (EXIT_SUCCESS);
}
