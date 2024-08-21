/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:27:06 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 15:03:50 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(long time, t_table *table)
{
	long	end;

	end = ft_gettimestamp() + time;
	while (ft_gettimestamp() < end && !ft_is_done(table))
		usleep(100);
}

static void	ft_setlasteat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = ft_gettimestamp();
	pthread_mutex_unlock(&philo->lock);
}

static void	ft_increment_eatcount(t_philo *philo)
{
	if (philo->table->timeto[MUST_EAT] != -1)
	{
		pthread_mutex_lock(&philo->lock);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->lock);
	}
}

static void	ft_feeder(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left);
	ft_print(philo, TAKEN_FORK);
	ft_print(philo, EAT);
	ft_setlasteat(philo);
	ft_usleep(philo->table->timeto[EAT], philo->table);
	ft_increment_eatcount(philo);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_getstarttime(philo->table) == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->timeto[EAT], philo->table);
	ft_setlasteat(philo);
	while (1)
	{
		if (ft_is_done(philo->table))
			break ;
		ft_feeder(philo);
		if (ft_is_done(philo->table))
			break ;
		ft_print(philo, SLEEP);
		ft_usleep(philo->table->timeto[SLEEP], philo->table);
		if (ft_is_done(philo->table))
			break ;
		ft_print(philo, THINK);
	}
	return (NULL);
}
