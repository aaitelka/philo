/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:00:56 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/31 02:30:30 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long	ft_getlasteat(t_philo *philo)
{
	long	last_eat;

	sem_wait(philo->table->sem[TIME]);
	last_eat = philo->last_eat;
	sem_post(philo->table->sem[TIME]);
	return (last_eat);
}

static void	ft_die(t_table *table, int *id)
{
	sem_wait(table->sem[LOCK]);
	table->is_done = true;
	sem_post(table->sem[LOCK]);
	sem_wait(table->sem[PRINT]);
	printf("%ld\t%d %s", ft_gettimestamp() - table->start_time, *id, MDIE);
	sem_post(table->sem[PRINT]);
}

static long	ft_geteatcount(t_philo *philo)
{
	long	eat_count;

	sem_wait(philo->table->sem[LOCK]);
	eat_count = philo->eat_count;
	sem_post(philo->table->sem[LOCK]);
	return (eat_count);
}

static void	ft_eating_done(t_table *table)
{
	sem_wait(table->sem[LOCK]);
	table->is_done = true;
	sem_post(table->sem[LOCK]);
}

void	*ft_observer(void *arg)
{
	t_philo	*philo;
	long	last_eat;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (true)
	{
		if (ft_geteatcount(philo) > (philo->table->timeto[MUST_EAT])
			&& philo->table->has_must_eat)
			(ft_eating_done(philo->table), exit(FULL));
		last_eat = ft_getlasteat(philo);
		if (last_eat == 0)
		{
			i = (i + 1) % philo->table->philo_count;
			continue ;
		}
		if (ft_gettimestamp() - last_eat >= philo->table->timeto[DIE])
			(ft_die(philo->table, &philo->id), exit(DEAD));
		i = (i + 1) % philo->table->philo_count;
	}
	return (NULL);
}
