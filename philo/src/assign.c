/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:41:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/08/17 14:07:23 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	swap(pthread_mutex_t *a, pthread_mutex_t *b)
{
	pthread_mutex_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	assign_forks(const t_table *table, t_philo *philo)
{
	philo->mtx_right = &(table->mtx_forks[philo->id]);
	philo->mtx_left = &(table->mtx_forks[(philo->id + table->size - 1) \
	% table->size]);
	if (philo->id + 1 == table->size)
		swap(philo->mtx_left, philo->mtx_right);
}

void	destroy(pthread_mutex_t *mutexes, size_t n)
{
	size_t	i;

	if (!mutexes)
		return ;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	free(mutexes);
}
