#include "philo.h"

bool	is_dead(t_philo *philo)
{
	unsigned long current_time;
	unsigned long time_since_last_meal;

	current_time = get_current_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	if (philo->intervals.die == 0)
	{
		printf("Error: die interval is 0. This should be checked.\n");
		return (false);
	}
	if (time_since_last_meal >= philo->intervals.die)
	{
		pthread_mutex_lock(&philo->locks->dead);
		if (philo->action != DEAD)
		{
			philo->action = DEAD;
			log_action(philo, "has died");
		}
		pthread_mutex_unlock(&philo->locks->dead);
		return (true);
	}
	return (false);
}

int init_mutexes(t_table *table) {
    size_t i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->size);
    if (!table->forks)
        return 1;

    for (i = 0; i < table->size; i++) {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0) {
            while (i > 0)
                pthread_mutex_destroy(&table->forks[--i]);
            free(table->forks);
            return 1;
        }
    }

    if (pthread_mutex_init(&table->locks.print, NULL) != 0 ||
        pthread_mutex_init(&table->locks.eat, NULL) != 0 ||
        pthread_mutex_init(&table->locks.dead, NULL) != 0) {
        for (i = 0; i < table->size; i++)
            pthread_mutex_destroy(&table->forks[i]);
        free(table->forks);
        return 1;
    }

    return 0;
}

void destroy_mutexes(t_table *table) {
    size_t i;

    for (i = 0; i < table->size; i++) {
        pthread_mutex_destroy(&table->forks[i]);
    }
    free(table->forks);

    pthread_mutex_destroy(&table->locks.print);
    pthread_mutex_destroy(&table->locks.eat);
    pthread_mutex_destroy(&table->locks.dead);
}

void init(t_table *table) {
    size_t i = 0;

    if (init_mutexes(table) != 0) {
        printf("Error: Mutex initialization failed.\n");
        return;
    }

    while (i < table->size) {
        if (pthread_create(&table->philosophers[i].thread, NULL, &act, (void *)&table->philosophers[i]) != 0) {
            printf("Error: pthread_create failed for philosopher %zu\n", i);
            return;
        }
        printf("Philosopher %zu thread created\n", i);
        i++;
    }

    i = 0;
    while (i < table->size) {
        if (pthread_join(table->philosophers[i].thread, NULL) != 0) {
            printf("Error: pthread_join failed for philosopher %zu\n", i);
        }
        printf("Philosopher %zu thread joined\n", i);
        i++;
    }

    destroy_mutexes(table);
}
