/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:27:06 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/30 18:00:32 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_usleep(long time, t_table *table)
{
	long	end;

	end = ft_gettimestamp() + time;
	while (ft_gettimestamp() < end && !ft_is_done(table))
		usleep(100);
}

static void	ft_setlasteat(t_philo *philo)
{
	sem_wait(philo->table->sem[TIME]);
	philo->last_eat = ft_gettimestamp();
	sem_post(philo->table->sem[TIME]);
}

static void	ft_increment_eatcount(t_philo *philo)
{
	if (philo->table->timeto[MUST_EAT] != -1)
	{
		sem_wait(philo->table->sem[ACCESS]);
		philo->eat_count++;
		sem_post(philo->table->sem[ACCESS]);
	}
}

static bool	ft_feeded(t_philo *philo)
{
	sem_wait(philo->table->sem[FORK]);
	ft_print(philo, TAKEN_FORK);
	if (philo->table->philo_count == 1)
		return (sem_post(philo->table->sem[FORK]), false);
	sem_wait(philo->table->sem[FORK]);
	ft_print(philo, TAKEN_FORK);
	ft_print(philo, EAT);
	ft_setlasteat(philo);
	ft_usleep(philo->table->timeto[EAT], philo->table);
	ft_increment_eatcount(philo);
	sem_post(philo->table->sem[FORK]);
	sem_post(philo->table->sem[FORK]);
	return (true);
}

void	ft_routine(t_philo	*philo)
{
	while (ft_getstarttime(philo->table) == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->timeto[EAT], philo->table);
	ft_setlasteat(philo);
	while (true)
	{
		// if (ft_is_done(philo->table))
		// 	ft_kilall(philo);
		if (ft_is_done(philo->table))
			kill(philo->philo, SIGKILL);
		if (!ft_feeded(philo))
			kill(philo->philo, SIGKILL);
		ft_print(philo, SLEEP);
		ft_usleep(philo->table->timeto[SLEEP], philo->table);
		// if (ft_is_done(philo->table))
		// 	ft_kilall(philo);
		ft_print(philo, THINK);
	}
}
