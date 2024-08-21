/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:24 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 02:48:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_locks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_mutex_init(&table->philos[index].fork, NULL) != SUCCES)
			return (EMUTEXINIT);
		if (pthread_mutex_init(&table->philos[index].lock, NULL) != SUCCES)
			return (EMUTEXINIT);
		index++;
	}
	if (pthread_mutex_init(&table->lock, NULL) != SUCCES)
		return (EMUTEXINIT);
	if (pthread_mutex_init(&table->print_lock, NULL) != SUCCES)
		return (EMUTEXINIT);
	return (SUCCES);
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
				&ft_routine, &philo[index]) != SUCCES)
			return (ECREATE);
		pthread_mutex_lock(&table->lock);
		table->start_time = gettimestamp();
		pthread_mutex_unlock(&table->lock);
		index++;
	}
	return (SUCCES);
}

static int	ft_join(t_table *table)
{
	t_philo	*philos;
	int		index;

	philos = table->philos;
	index = 0;
	if (table->philo_count == 1)
	{
		if (pthread_detach(philos->philo) != SUCCES)
			return (EJOIN);
	}
	else
	{
		while (index < table->philo_count)
		{
			if (pthread_join(philos[index].philo, NULL) != SUCCES)
				return (EJOIN);
			index++;
		}
	}
	return (SUCCES);
}

static int	ft_table(t_table *table, char **argv)
{
	int	index;
	int	args;

	index = -1;
	while (++index < 3)
		table->timeto[index] = to_long(argv[index + 2]);
	if (argv[5])
		table->timeto[MUST_EAT] = to_long(argv[5]);
	else
		table->timeto[MUST_EAT] = -1;
	index = -1;
	while (++index < table->philo_count)
		table->philos[index].id = index + 1;
	table->is_done = false;
	args = check_args(table);
	if (args != SUCCES)
		return (args);
	return (SUCCES);
}

void	simulate(t_table *table, char **argv)
{
	table->philo_count = to_long(argv[1]);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_logger(EALLOCATE));
	memset(table->philos, 0, sizeof(t_philo) * table->philo_count);
	if (ft_table(table, argv) != SUCCES)
		return (ft_logger(EARGS));
	if (ft_locks(table) != SUCCES)
		return (ft_logger(EMUTEXINIT));
	if (ft_philos(table, table->philos) != SUCCES)
		return (ft_logger(ECREATE));
	observer(table);
	if (ft_join(table) != SUCCES)
		return (ft_logger(EJOIN));
}
