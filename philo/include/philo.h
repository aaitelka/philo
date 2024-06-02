/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:39:23 by aaitelka          #+#    #+#             */
/*   Updated: 2024/06/02 00:30:58 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>

# define ERR_ALLOCATION "Error allocation, maybe malloc failed\n"
# define ERR_THREAD_CREATE "Error creating new thread\n"
# define ERR_THREAD_JOIN "Error joining thread\n"
# define ERR_MUTEX_INIT "Error init mutex\n"

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
	int				count;
	long			time_to[4];
	pthread_t		*philos;
	pthread_mutex_t	*forks;
}	t_philo;

#endif