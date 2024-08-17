/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_time.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:42:21 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 13:53:55 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_init_time(t_table *table, size_t i)
{
	if (i == table->size)
		atomic_set(table->mtx_act, &table->init_time, get_current_time());
	else
		atomic_set(table->mtx_act, &table->init_time, -1);
}

int	wait_for_init_time_is_set(t_philo *philo)
{
	t_table	*table;
	long	init_time;

	table = philo->table;
	while (atomic_get(table->mtx_act, &table->init_time) == 0)
		continue ;
	init_time = table->init_time;
	if (init_time == -1)
		return (1);
	atomic_set(philo->mtx_philo, &philo->last_meal_time, init_time);
	return (0);
}
