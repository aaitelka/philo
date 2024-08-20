/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:24 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 15:39:54 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_locks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_mutex_init(&table->philos[index].fork, NULL) != SUCCES)
			return (EMUTEXINIT);
		index++;
	}
	if (pthread_mutex_init(&table->lock, NULL) != SUCCES)
		return (EMUTEXINIT);
	if (pthread_mutex_init(&table->print_lock, NULL) != SUCCES)
		return (EMUTEXINIT);
	// if (pthread_mutex_init(&table->observer_lock, NULL) != SUCCES)
	// 	return (EMUTEXINIT);
	return (SUCCES);
}

static int	create_philos(t_table *table, t_philo *philo)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if  (index > 0)
			philo[index].left = &philo[index - 1].fork;
		if (index == 0)
			philo[index].left = &philo[table->philo_count - 1].fork;
		philo[index].table = table;
		philo[index].eat_count = 0;
		// philo[index].start_time = get_timestamp();
		if (pthread_create(&philo[index].philo, NULL, \
				&ft_routine, &philo[index]) != SUCCES)
			return (ECREATE);
		index++;
	}
	return (SUCCES);
}

static int	join_philos(t_table *table)
{
	t_philo	*philos;
	int		index;

	philos = table->philos;
	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_join(philos[index].philo, NULL) != SUCCES)
			return (EJOIN);
		index++;
	}
	return (SUCCES);
}

static int	init_table(t_table *table, char **argv)
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

void	create_table(t_table *table, char **argv)
{
	table->philo_count = to_long(argv[1]);
	table->start_time = get_timestamp();
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_logger(EALLOCATE));
	if (init_table(table, argv) != SUCCES)
		return (ft_logger(EARGS));
	if (init_locks(table) != SUCCES)
		return (ft_logger(EMUTEXINIT));
	if (create_philos(table, table->philos) != SUCCES)
		return (ft_logger(ECREATE));
	if (join_philos(table) != SUCCES)
		return (ft_logger(EJOIN));
}
