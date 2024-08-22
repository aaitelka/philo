/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/22 03:43:07 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ERROR -1
# define SUCCESS 0
# define FAILURE 1
# define MINTIME 60

# define MTAKEN_FORK " has taken a fork"
# define MEAT " is eating"
# define MSLEEP " is sleeping"
# define MTHINK " is thinking"
# define MDIE " died"

# define MEARGS "Error: Invalid arguments\n"
# define MEJOIN "Error: pthread_join failed\n"
# define MECREATE "Error: pthread_create failed\n"
# define MEGETTIME "Error: gettimeofday failed\n"
# define MEALLOCATE "Error: allocation, malloc failed\n"
# define MEMUTEXINIT "Error: pthread_mutex_init failed\n"
# define MEMUTEXLOCK "Error: pthread_mutex_lock failed\n"
# define MEOUTOFRANGE "Error: number of philosophers out of range\n"
# define MEMUTEXDESTROY "Error: pthread_mutex_destroy failed\n"

typedef enum e_state
{
	DIE,
	EAT,
	SLEEP,
	MUST_EAT,
	THINK,
	TAKEN_FORK,
}	t_state;

typedef enum e_code
{
	EARGS,
	EJOIN,
	ECREATE,
	EGETTIME,
	EALLOCATE,
	EMUTEXINIT,
	EMUTEXLOCK,
	EOUTOFRANGE,
	EMUTEXDESTROY,
}	t_code;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	long			eat_count;
	t_table			*table;
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left;
}	t_philo;

struct s_table
{
	int				philo_count;
	long			timeto[4];
	long			start_time;
	bool			is_done;
	bool			has_must_eat;
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;
};

int		ft_check_args(t_table *table);
long	ft_gettimestamp(void);
long	ft_tolong(const char *str);
long	ft_getstarttime(t_table *table);
void	ft_error(const char *str);
void	ft_observer(t_table *table);
void	ft_simulate(t_table *table, char **av);
void	ft_print(t_philo *philo, t_state state);
void	*ft_routine(void *arg);
bool	ft_is_done(t_table *table);

#endif
