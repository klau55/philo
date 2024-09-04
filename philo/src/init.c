/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:42:09 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/09/04 16:11:32 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_pthreads(t_table *table, int size)
{
	int	i;

	i = 0;
	pthread_join(*(table->monitor), NULL);
	while (i < size)
	{
		pthread_join(table->threads[i], NULL);
		i++;
	}
}

bool	init(t_table *table)
{
	size_t	i;

	pthread_mutex_lock(table->mtx_act);
	if (pthread_create(table->monitor, NULL, monitoring, (void *) table) != 0)
		return (false);
	i = 0;
	while (i < table->size)
	{
		if (pthread_create(&table->threads[i], NULL, \
			act, (void *)&((table->philosophers)[i])) != 0)
		{
			ft_putstr_fd("Error: philosopher thread_create failed\n", 2);
			break ;
		}
		i++;
	}
	set_init_time(table, i);
	pthread_mutex_unlock(table->mtx_act);
	join_pthreads(table, i);
	return (i == table->size);
}
