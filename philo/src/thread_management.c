/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:04:18 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 14:22:09 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	allocate_threads(t_table *table)
{
	table->monitor = ft_calloc(1, sizeof(pthread_t));
	if (!table->monitor)
		return (false);
	table->threads = ft_calloc(table->size, sizeof(pthread_t));
	if (!table->threads)
	{
		free(table->monitor);
		return (false);
	}
	return (true);
}

/**
 * Allocate table's arrays.
 */
bool	allocate(t_table *table)
{
	if (!allocate_mutexes(&(table->mtx_forks), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_philosophers), table->size))
		return (false);
	if (!allocate_mutexes(&(table->mtx_act), 1))
		return (false);
	if (!allocate_philosophers(table, table->size))
		return (false);
	if (!allocate_threads(table))
	{
		destroy_and_free(table);
		return (false);
	}
	return (true);
}

bool	allocate_mutexes(pthread_mutex_t **mutexes, size_t size)
{
	pthread_mutex_t	*tmp;
	size_t			i;

	tmp = ft_calloc(size, sizeof(pthread_mutex_t));
	if (!tmp)
		return (false);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&tmp[i], NULL) != 0)
		{
			destroy(tmp, i);
			return (false);
		}
		i++;
	}
	*mutexes = tmp;
	return (true);
}

bool	allocate_philosophers(t_table *table, size_t size)
{
	t_philo	*philosophers;
	size_t	i;

	philosophers = ft_calloc(size, sizeof(t_philo));
	if (!philosophers)
		return (false);
	i = 0;
	while (i < size)
	{
		philosophers[i].id = i;
		philosophers[i].table = table;
		assign_forks(table, &philosophers[i]);
		philosophers[i].mtx_philo = &table->mtx_philosophers[i];
		i++;
	}
	table->philosophers = philosophers;
	return (true);
}
