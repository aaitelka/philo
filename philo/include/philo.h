/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 15:55:14 by aaitelka         ###   ########.fr       */
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
	int				last_eat;
	int				eat_count;
	t_table			*table;
	pthread_t		philo;
	pthread_mutex_t	fork;
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
	pthread_mutex_t	observer_lock;
};

int		check_args(t_table *table);
long	get_timestamp();
long	to_long(const char *str);
void	ft_logger(t_code code);
void	observer(t_philo *philo);
void	create_table(t_table *table, char **av);
void	ft_print(t_philo *philo, t_state state);
void	*ft_routine(void *arg);

#endif
