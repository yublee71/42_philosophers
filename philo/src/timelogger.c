/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timelogger.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:24:23 by yublee            #+#    #+#             */
/*   Updated: 2024/12/21 17:36:14 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*timelogger(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	(void)table;
	return (NULL);
}