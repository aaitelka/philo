/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:24 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/12 18:59:50 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int init_locks(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_mutex_init(&table->philos[index].fork, NULL) != SUCCES)
			return (EMUTEXINIT);
		index++;
	}
	return (SUCCES);
}

static int create_philos(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->philo_count)
	{
		if (pthread_create(&table->philos[index].philo, NULL, &routine, table) != SUCCES)
			return (ECREATE);
		index++;
	}
	return (SUCCES);
}

static int join_philos(t_philo *philos)
{
	int	index;

	index = 0;
	while (philos[index].id)
	{
		if (pthread_join(philos[index].philo, NULL) != SUCCES)
			return (EJOIN);
		index++;
	}
	return (SUCCES);
}

static void set_ids(t_philo *philos, int size)
{
	int				index;
	pthread_mutex_t	lock;

	index = 0;
	while (index < size)
	{
		philos[index].id = index + 1;
		index++;
	}
}

static int	init_table(t_table *table, char **argv)
{
	int	index;
	int	args;

	index = -1;
	while (++index < 3)
		table->timeto[index] = to_long(argv[index + 2]);
	if(argv[5])
		table->timeto[MUST_EAT] = to_long(argv[5]);
	else
		table->timeto[MUST_EAT] = -1;
	table->start_time = get_timestamp();
	set_ids(table->philos, table->philo_count);
	args = check_args(table);
	if (args != SUCCES)
		return (args);
	return (SUCCES);
}

void	create_table(t_table *table, char **argv)
{
	table->philo_count = to_long(argv[1]);
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_logger(EALLOCATE));
	if (init_table(table, argv) != SUCCES)
		return (ft_logger(EARGS));
	if (init_locks(table) != SUCCES)
		return (ft_logger(EMUTEXINIT));
	if (create_philos(table) != SUCCES)
		return (ft_logger(ECREATE));
	if (table->start_time == -1)
		return (ft_logger(EGETTIME));
	if (join_philos(table->philos) != SUCCES)
		return (ft_logger(EJOIN));
}
