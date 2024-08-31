/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization_time.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:42:21 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/31 14:56:52 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_init_time(t_table *table, size_t i)
{
	if (i == table->size)
		table->init_time = get_current_time();
	else
		table->init_time = -1;
}

int	wait_for_init_time_is_set(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_meal_time = atomic_get(table->mtx_act, &table->init_time);
	if (philo->last_meal_time == -1)
		return (1);
	return (0);
}
