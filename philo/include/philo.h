/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 02:25:18 by aaitelka         ###   ########.fr       */
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
# define SUCCES 0
# define FAILURE 1
# define MINTIME 60

# define MTAKEN_FORK " has taken a fork"
# define MEAT " is eating"
# define MSLEEP " is sleeping"
# define MTHINK " is thinking"
# define MDIE " died"

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
	EOUTOFRANGE,
	EMUTEXLOCK,
	ERROR_COUNT
}	t_code;

typedef struct s_table t_table;

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
	bool			is_done;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	lock;
	pthread_mutex_t	print_lock;

};

int		check_args(t_table *table);
long	gettimestamp(void);
long	to_long(const char *str);
long	getstarttime(t_table *table);
void	ft_logger(t_code code);
void	observer(t_table *table);
void	simulate(t_table *table, char **av);
void	ft_print(t_philo *philo, t_state state);
void	*ft_routine(void *arg);

#endif
