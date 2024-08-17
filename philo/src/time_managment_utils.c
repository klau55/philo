/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_managment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:44:10 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 13:48:41 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	curr_time;
	long			timestamp;

	gettimeofday(&curr_time, NULL);
	timestamp = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (timestamp);
}

void	ft_usleep(int msec, t_table *table)
{
	long	usleep_start;

	usleep_start = get_current_time();
	while (get_current_time() - usleep_start < msec
		&& atomic_get(table->mtx_act, &table->game_over) == 0)
		usleep(500);
}

int	calculate_action_gap(t_time die, t_time eat, t_time sleep)
{
	int	action_gap;

	action_gap = (die - (eat + sleep)) / 2;
	if (action_gap < 0)
		action_gap = 0;
	return (action_gap);
}
