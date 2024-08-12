/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/12 17:09:21 by aaitelka         ###   ########.fr       */
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

# define ERROR -1
# define SUCCES 0
# define FAILURE 1
# define MINTIME 60

enum e_state
{
	DIE,
	EAT,
	SLEEP,
	MUST_EAT,
};

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

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_table
{
	int				philo_count;
	long			start_time;
	long			timeto[4];
	t_philo			*philos;
}	t_table;

void	create_table(t_table *table, char **av);

/** TIME */
long	get_timestamp();

/** PARSER */
long	to_long(const char *str);
int		check_args(t_table *table);

/** LOGGER */
void	ft_logger(t_code code);
void	*routine(void *arg);

#endif