/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:38:47 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/28 16:24:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_getlasteat(t_philo *philo)
{
	long	last_eat;

	pthread_mutex_lock(&philo->lock);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(&philo->lock);
	return (last_eat);
}

static long	ft_geteatcount(t_philo *philo)
{
	long	eat_count;

	pthread_mutex_lock(&philo->lock);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->lock);
	return (eat_count);
}

static void	ft_die(t_table *table, int *i)
{
	pthread_mutex_lock(&table->lock);
	table->is_done = true;
	pthread_mutex_unlock(&table->lock);
	pthread_mutex_lock(&table->print_lock);
	printf("%ld\t%d %s\n", ft_gettimestamp() - table->start_time,
		table->philos[*i].id, MDIE);
	pthread_mutex_unlock(&table->print_lock);
}

static void	ft_eating_done(t_table *table)
{
	pthread_mutex_lock(&table->lock);
	table->is_done = true;
	pthread_mutex_unlock(&table->lock);
}

void	ft_observer(t_table *table)
{
	long	last_eat;
	int		i;

	i = 0;
	while (true)
	{
		if (ft_geteatcount(&table->philos[i]) > (table->timeto[MUST_EAT])
			&& table->has_must_eat)
		{
			ft_eating_done(table);
			break ;
		}
		last_eat = ft_getlasteat(&table->philos[i]);
		if (last_eat == 0)
		{
			i = (i + 1) % table->philo_count;
			continue ;
		}
		if (ft_gettimestamp() - last_eat >= table->timeto[DIE])
		{
			ft_die(table, &i);
			break ;
		}
		i = (i + 1) % table->philo_count;
	}
}
