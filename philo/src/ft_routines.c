/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:27:06 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 15:14:05 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(long time)
{
	long	start;
	long	end;

	start = get_timestamp();
	end = start + time;
	while (get_timestamp() < end)
		usleep(10);
}

static void	ft_feeder(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->left);
	ft_print(philo, TAKEN_FORK);
	ft_print(philo, EAT);
	ft_usleep(philo->table->timeto[EAT]);
	philo->eat_count++;
	philo->last_eat = get_timestamp();
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (true)
	{
		ft_feeder(philo);
		ft_print(philo, SLEEP);
		ft_usleep(philo->table->timeto[SLEEP]);
		ft_print(philo, THINK);
	}
	return (NULL);
}
