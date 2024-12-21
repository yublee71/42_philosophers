/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:53:49 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 14:34:34by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"



int	main(int argc, char **argv)
{
	t_info			info;
	t_table			table;

	if (init_info(argc, argv, &info) < 0
		|| init_table(&table, info) < 0)
		return (1);
	start_table_simulation(&table);
	cleanup_table_simulation(&table);
	return (0);
}