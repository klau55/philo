/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:43:26 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/31 15:26:50 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dead(t_philo *philo)
{
	long	last_meal_time;

	last_meal_time = philo->last_meal_time;
	if (last_meal_time == 0)
		last_meal_time = philo->table->init_time;
	if (get_current_time() - last_meal_time >= philo->table->die)
	{
		printf("%ld\t%ld\t%s", get_current_time() - philo->table->init_time \
		, philo->id + 1, "has died\n");
		philo->table->game_over = 1;
		return ;
	}
	return ;
}

static int	is_game_over(t_philo *philo)
{
	pthread_mutex_lock(philo->table->mtx_act);
	if (philo->table->satiation_count == philo->table->size)
	{
		philo->table->game_over = 1;
		pthread_mutex_unlock(philo->table->mtx_act);
		return (1);
	}
	is_dead(philo);
	pthread_mutex_unlock(philo->table->mtx_act);
	return (philo->table->game_over);
}

void	*monitoring(void *arg)
{
	t_table		*table;
	size_t		i;

	table = (t_table *)arg;
	if (atomic_get(table->mtx_act, &table->init_time) == -1)
		return (NULL);
	ft_usleep(30, table);
	while (true)
	{
		i = 0;
		while (i < table->size)
		{
			if (is_game_over(&table->philosophers[i++]))
				return (NULL);
		}
	}
	return (NULL);
}
