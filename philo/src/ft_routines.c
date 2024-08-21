/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:27:06 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 02:45:23 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_done(t_table *table)
{
	bool	done;

	pthread_mutex_lock(&table->lock);
	done = table->is_done;
	pthread_mutex_unlock(&table->lock);
	return (done);
}

static void	ft_usleep(long time, t_table *table)
{
	long	end;

	end = gettimestamp() + time;
	while (gettimestamp() < end && !is_done(table))
		usleep(100);
}

static void	set_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = gettimestamp();
	pthread_mutex_unlock(&philo->lock);
}

static void	ft_feeder(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left);
	ft_print(philo, TAKEN_FORK);
	ft_print(philo, EAT);
	set_last_eat(philo);
	ft_usleep(philo->table->timeto[EAT], philo->table);
	pthread_mutex_lock(&philo->lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (getstarttime(philo->table) == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->timeto[EAT], philo->table);
	set_last_eat(philo);
	while (1)
	{
		if (is_done(philo->table))
			break ;
		ft_feeder(philo);
		if (is_done(philo->table))
			break ;
		ft_print(philo, SLEEP);
		ft_usleep(philo->table->timeto[SLEEP], philo->table);
		if (is_done(philo->table))
			break ;
		ft_print(philo, THINK);
	}
	return (NULL);
}
