/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/07/15 12:03:34 by aaitelka         ###   ########.fr       */
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
//should remove
#include <ctype.h>
#include <limits.h>

# define EGETTIME "Error getting time, maybe gettimeofday failed\n"
# define EALLOCATE "Error allocation, maybe malloc failed\n"
# define ECREATE "Error creating new thread\n"
# define EJOIN "Error joining thread\n"
# define EMUTEXINIT "Error init mutex\n"
# define SUCCES 0

typedef enum e_state
{
	DIE,
	EAT,
	SLEEP,
	MUST_EAT,
}	e_state;

typedef struct s_philo
{
	int				id;
	int				count;
	int				should_eat;
	int				forks_count;
	long			time_to[4];
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_philo;

#endif