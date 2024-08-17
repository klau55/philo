/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:42:30 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 14:02:13 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	log_action(t_philo *philo, long timestamp, char *act_msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(table->mtx_act);
	if (table->game_over == 0)
	{
		printf("%zu\t%zu\t%s", timestamp - table->init_time, \
		philo->id + 1, act_msg);
		pthread_mutex_unlock(table->mtx_act);
		return (false);
	}
	pthread_mutex_unlock(table->mtx_act);
	return (true);
}
