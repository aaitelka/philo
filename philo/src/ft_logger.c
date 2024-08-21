/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:21:01 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 02:26:02 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log(const char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

static bool	is_done(t_table *table)
{
	bool	done;

	pthread_mutex_lock(&table->lock);
	done = table->is_done;
	pthread_mutex_unlock(&table->lock);
	return (done);
}

void	ft_logger(t_code code)
{
	static const char	*errors[8] = {0};

	if (errors[EARGS] == NULL)
	{
		errors[EARGS] = "Error: wrong argument\n";
		errors[EJOIN] = "Error: joining thread\n";
		errors[ECREATE] = "Error: pthread_create: failed\n";
		errors[EGETTIME] = "Error: gettimeofday: failed\n";
		errors[EALLOCATE] = "Error: allocation, malloc failed\n";
		errors[EMUTEXINIT] = "Error: pthread_mutex_init: failed\n";
		errors[EOUTOFRANGE] = "Error: number of philosophers out of range\n";
		errors[EMUTEXLOCK] = "Error: pthread_mutex_lock: failed\n";
	}
	if (code >= 0 && code < ERROR_COUNT)
		log(errors[code], STDERR_FILENO);
	else
		log("Error: unknown error occured\n", STDERR_FILENO);
}

long	getstarttime(t_table *table)
{
	long	time;

	pthread_mutex_lock(&table->lock);
	time = table->start_time;
	pthread_mutex_unlock(&table->lock);
	return (time);
}

void	ft_print(t_philo *philo, t_state state)
{
	int		id;
	long	time;

	id = philo->id;
	pthread_mutex_lock(&philo->table->print_lock);
	if (!is_done(philo->table))
	{
		time = getstarttime(philo->table);
		if (state == TAKEN_FORK)
			printf("%ld\t%d %s\n", gettimestamp() - time, id, MTAKEN_FORK);
		else if (state == EAT)
			printf("%ld\t%d %s\n", gettimestamp() - time, id, MEAT);
		else if (state == SLEEP)
			printf("%ld\t%d %s\n", gettimestamp() - time, id, MSLEEP);
		else if (state == THINK)
			printf("%ld\t%d %s\n", gettimestamp() - time, id, MTHINK);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}
