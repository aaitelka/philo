/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:59:32 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/31 02:26:02 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

# define ERROR -1
# define SUCCESS 0
# define FAILURE 1
# define MINTIME 60

# define FULL 99
# define DEAD 11

# define NFORK "/fork"
# define NTIME "/time"
# define NLOCK "/lock"
# define NPRINT "/print"
# define NACCESS "/access"

# define MTAKEN_FORK " has taken a fork\n"
# define MEAT " is eating\n"
# define MSLEEP " is sleeping\n"
# define MTHINK " is thinking\n"
# define MDIE " died\n"

# define MEFORK "Error: fork failed\n"
# define MEARGS "Error: Invalid arguments\n"
# define MEWAIT "Error: waiting processes failed\n"
# define MECREATE "Error: pthread_create failed\n"
# define MEGETTIME "Error: gettimeofday failed\n"
# define MEALLOCATE "Error: allocation, malloc failed\n"
# define MEMUTEXINIT "Error: semaphore failed to init or open\n"
# define MEMUTEXLOCK "Error: semaphore failed to lock\n"
# define MEOUTOFRANGE "Error: number of philosophers out of range\n"
# define MEMUTEXDESTROY "Error: sem_close or sem_unlink failed\n"

typedef enum e_state
{
	DIE,
	EAT,
	SLEEP,
	MUST_EAT,
	THINK,
	TAKEN_FORK,
	DONE,
}	t_state;

enum e_code
{
	EFORK,
	EARGS,
	EJOIN,
	ECREATE,
	EGETTIME,
	EALLOCATE,
	EMUTEXINIT,
	EMUTEXLOCK,
	EOUTOFRANGE,
	EMUTEXDESTROY,
};

enum e_forks
{
	FORK,
	LOCK,
	TIME,
	PRINT,
	ACCESS,
	SEM_SIZE,
};

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	long		last_eat;
	long		eat_count;
	pid_t		philo;
	t_table		*table;
	pthread_t	observer;
}	t_philo;

struct s_table
{
	int		philo_count;
	long	timeto[4];
	long	start_time;
	bool	is_done;
	bool	has_must_eat;
	char	**name;
	sem_t	*sem[SEM_SIZE];
	t_philo	*philos;
};

int		ft_check_args(t_table *table);
long	ft_gettimestamp(void);
long	ft_tolong(const char *str);
long	ft_getstarttime(t_table *table);
void	ft_error(const char *str);
void	*ft_observer(void *arg);
void	ft_simulate(t_table *table, char **av);
void	ft_print(t_philo *philo, t_state state);
void	ft_routine(t_philo	*philo);
bool	ft_is_done(t_table *table);
void	ft_unlink_all(t_table *table);

#endif
