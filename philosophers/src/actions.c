#include "philo.h"

bool do_eat(t_philo *philo) {
    printf("Philosopher %zu attempting to eat\n", philo->id);

    printf("Philosopher %zu attempting to lock right fork %zu\n", philo->id, philo->id);
    pthread_mutex_lock(philo->right);
    log_action(philo, "has taken right fork");

    printf("Philosopher %zu attempting to lock left fork %zu\n", philo->id, (philo->id + philo->table_size - 1) % philo->table_size);
    pthread_mutex_lock(philo->left);
    log_action(philo, "has taken left fork");

    if (is_dead(philo)) {
        pthread_mutex_unlock(philo->right);
        pthread_mutex_unlock(philo->left);
        return false;
    }

    philo->action = EAT;
    pthread_mutex_lock(&philo->locks->eat);
    log_action(philo, "is eating");
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->locks->eat);

    ft_safe_usleep(philo->intervals.eat, philo);

    pthread_mutex_unlock(philo->left);
    log_action(philo, "has put down left fork");
    pthread_mutex_unlock(philo->right);
    log_action(philo, "has put down right fork");

    printf("Philosopher %zu finished eating\n", philo->id);

    return true;
}

bool do_sleep(t_philo *philo) {
    if (is_dead(philo))
        return false;
    philo->action = SLEEP;
    log_action(philo, "is sleeping");
    printf("Philosopher %zu is sleeping\n", philo->id);
    ft_safe_usleep(philo->intervals.sleep, philo);
    printf("Philosopher %zu finished sleeping\n", philo->id);
    return true;
}

bool do_think(t_philo *philo) {
    if (is_dead(philo))
        return false;
    philo->action = THINK;
    log_action(philo, "is thinking");
    printf("Philosopher %zu is thinking\n", philo->id);
    return true;
}

void *act(void *philo_ptr) {
    t_philo *philo = (t_philo *)philo_ptr;

    if (philo->id % 2 == 1) {
        if (!do_think(philo)) {
            printf("Philosopher %zu failed to start thinking\n", philo->id);
            return NULL;
        }
        ft_safe_usleep(philo->intervals.eat / 2, philo);
    }

    while (!is_dead(philo)) {
        if (philo->action == EAT) {
            if (!do_eat(philo)) {
                printf("Philosopher %zu failed to eat\n", philo->id);
                return NULL;
            }
            philo->action = SLEEP;
        } else if (philo->action == SLEEP) {
            if (!do_sleep(philo)) {
                printf("Philosopher %zu failed to sleep\n", philo->id);
                return NULL;
            }
            philo->action = THINK;
        } else if (philo->action == THINK) {
            if (!do_think(philo)) {
                printf("Philosopher %zu failed to think\n", philo->id);
                return NULL;
            }
            philo->action = EAT;
        }
    }
    return NULL;
}
