/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:21:01 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 15:39:25 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	log(const char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
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

void	ft_print(t_philo *philo, t_state state)
{
	int		id;
	long	time;

	id = philo->id;
	pthread_mutex_lock(&philo->table->print_lock);
	time = philo->table->start_time;
	if (state == TAKEN_FORK)
		printf("%ld\t%d %s\n", get_timestamp() - time, id, " has taken a fork");
	else if (state == EAT)
		printf("%ld\t%d %s\n", get_timestamp() - time, id, " is eating");
	else if (state == SLEEP)
		printf("%ld\t%d %s\n", get_timestamp() - time, id, " is sleeping");
	else if (state == THINK)
		printf("%ld\t%d %s\n", get_timestamp() - time, id, " is thinking");
	else if (state == DIE)
		printf("%ld\t%d %s\n", get_timestamp() - time, id, " died");
	pthread_mutex_unlock(&philo->table->print_lock);
}
