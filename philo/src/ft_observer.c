/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_observer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:38:47 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 02:56:16 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	getlasteat(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(&philo->lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->lock);
	return (last_eat);
}

static void	ft_die(t_table *table, int *i)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld\t%d %s\n", gettimestamp() - table->start_time,
		table->philos[*i].id, " died");
	pthread_mutex_unlock(&table->print_lock);
	pthread_mutex_lock(&table->lock);
	table->is_done = true;
	pthread_mutex_unlock(&table->lock);
}

void	observer(t_table *table)
{
	int		i;
	long	time;

	i = 0;
	while (true)
	{
		if (getlasteat(&table->philos[i]) == 0)
		{
			i++;
			if (i == table->philo_count)
				i = 0;
			continue ;
		}
		time = gettimestamp() - getlasteat(&table->philos[i]);
		if (time >= table->timeto[DIE])
		{
			ft_die(table, &i);
			break ;
		}
		i++;
		if (i == table->philo_count)
			i = 0;
	}
}
