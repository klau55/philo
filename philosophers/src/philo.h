#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// Define the time type
typedef size_t t_time;

// Define intervals structure
typedef struct s_intervals {
    t_time die;
    t_time eat;
    t_time sleep;
    t_time start;
} t_intervals;

// Define locks structure
typedef struct s_locks {
    pthread_mutex_t print;
    pthread_mutex_t eat;
    pthread_mutex_t dead;
} t_locks;

// Define action enumeration
typedef enum e_action {
    EAT,
    SLEEP,
    THINK,
    DEAD
} t_action;

// Define philosopher structure
typedef struct s_philo {
    size_t id;
    t_action action;
    pthread_t thread;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    t_locks *locks;
    t_intervals intervals;
    long last_meal_time;
    size_t table_size;
} t_philo;

// Define table structure
typedef struct s_table {
    size_t size;
    pthread_mutex_t *forks;
    t_philo *philosophers;
    t_locks locks;
    t_intervals intervals;
} t_table;

// Function prototypes
t_table allocate(const t_intervals intervals, size_t size);
void assign(t_table *table);
t_philo *allocate_philos(const size_t size, t_locks *locks, t_intervals intervals);
void init(t_table *table);
bool is_dead(t_philo *philo);
long get_current_time(void);
int ft_safe_usleep(t_time duration, t_philo *philo);
void destroy_and_free(t_table *table);
void log_action(t_philo *philo, const char *event_message);
void *act(void *philo_ptr);
long get_current_time(void);

// Action functions
bool do_eat(t_philo *philo);
bool do_sleep(t_philo *philo);
bool do_think(t_philo *philo);

#endif
