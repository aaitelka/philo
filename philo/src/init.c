/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:24 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/22 03:21:16 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_locks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_mutex_init(&table->philos[index].fork, NULL) != SUCCESS)
			return (EMUTEXINIT);
		if (pthread_mutex_init(&table->philos[index].lock, NULL) != SUCCESS)
			return (EMUTEXINIT);
		index++;
	}
	if (pthread_mutex_init(&table->lock, NULL) != SUCCESS)
		return (EMUTEXINIT);
	if (pthread_mutex_init(&table->print_lock, NULL) != SUCCESS)
		return (EMUTEXINIT);
	return (SUCCESS);
}

static int	ft_philos(t_table *table, t_philo *philo)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (index > 0)
			philo[index].left = &philo[index - 1].fork;
		if (index == 0)
			philo[index].left = &philo[table->philo_count - 1].fork;
		philo[index].table = table;
		if (pthread_create(&philo[index].philo, NULL, \
				&ft_routine, &philo[index]) != SUCCESS)
			return (ECREATE);
		pthread_mutex_lock(&table->lock);
		table->start_time = ft_gettimestamp();
		pthread_mutex_unlock(&table->lock);
		index++;
	}
	return (SUCCESS);
}

static int	ft_join(t_table *table)
{
	t_philo	*philos;
	int		index;

	philos = table->philos;
	index = 0;
	if (table->philo_count == 1)
	{
		if (pthread_detach(philos->philo) != SUCCESS)
			return (EJOIN);
	}
	else
	{
		while (index < table->philo_count)
		{
			if (pthread_join(philos[index].philo, NULL) != SUCCESS)
				return (EJOIN);
			index++;
		}
	}
	return (SUCCESS);
}

static int	ft_table(t_table *table, char **argv)
{
	int	index;
	int	args;

	index = -1;
	while (++index < 3)
		table->timeto[index] = ft_tolong(argv[index + 2]);
	if (argv[5])
	{
		table->timeto[MUST_EAT] = ft_tolong(argv[5]);
		table->has_must_eat = true;
	}
	else
		table->timeto[MUST_EAT] = -1;
	index = -1;
	while (++index < table->philo_count)
		table->philos[index].id = index + 1;
	table->is_done = false;
	args = ft_check_args(table);
	if (args != SUCCESS)
		return (args);
	return (SUCCESS);
}

void	ft_simulate(t_table *table, char **argv)
{
	table->philo_count = ft_tolong(argv[1]);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_error(MEALLOCATE));
	memset(table->philos, 0, sizeof(t_philo) * table->philo_count);
	if (ft_table(table, argv) != SUCCESS)
		return (ft_error(MEARGS));
	if (ft_locks(table) != SUCCESS)
		return (ft_error(MEMUTEXINIT));
	if (ft_philos(table, table->philos) != SUCCESS)
		return (ft_error(MECREATE));
	ft_observer(table);
	if (ft_join(table) != SUCCESS)
		return (ft_error(MEJOIN));
}
