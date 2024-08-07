/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:21:24 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/07 12:32:28 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	to_long(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

static void	assert_error(t_code code)
{
	char	*error[7];
	int		i;
	int		size;

	i = -1;
	error[EARGS] = "Error: wrong argument\n";
	error[EJOIN] = "Error: joining thread\n";
	error[ECREATE] = "Error: pthread_create: failed\n";
	error[EGETTIME] = "Error: gettimeofday: failed\n";
	error[EALLOCATE] = "Error: allocation, malloc failed\n";
	error[EMUTEXINIT] = "Error: pthread_mutex_init: failed\n";
	error[EOUTOFRANGE] = "Error: number of philosophers out of range\n";
	size = sizeof(error) / sizeof(error[0]);
	while (++i < size)
	{
		if (i == (int)code)
		{
			printf("%s", error[i]);
			break ;
		}
	}
}

static int	check_args(t_table *table)
{
	if (table->timeto[DIE] < MINTIME || table->timeto[EAT] < MINTIME
		|| table->timeto[SLEEP] < MINTIME || table->timeto[MUST_EAT] < 0)
		return (-1);
	else if (table->philo_count > 200)
		return (EOUTOFRANGE);
	return (SUCCES);
}

static int	init(t_table *table, char **av)
{
	int	i;
	int	args;
	
	i = -1;
	table->philo_count = to_long(av[1]);
	while (++i < 3)
		table->timeto[i] = to_long(av[i + 2]);
	table->timeto[MUST_EAT] = (av[5]) ? to_long(av[5]) : -1;
		printf("must eat = %ld\n", table->timeto[MUST_EAT]);
	args = check_args(table);
	if (args != SUCCES)
		return (args);
	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = (i + 1);
		if (pthread_mutex_init(&table->philos[i].fork, NULL) != SUCCES)
			return (EMUTEXINIT);
	}
	return (SUCCES);
}

void	create(t_table *table, char **av, void *(*rout)(void *))
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * to_long(av[1]));
	if (!table->philos)
		return (assert_error(EALLOCATE));
	if (init(table, av) != SUCCES)
		return (assert_error(EARGS));
	while (table->philos[++i].id)
	{
		if (pthread_create(&table->philos[i].philo, NULL, \
			rout, &table->philos[i]) != SUCCES)
			return (assert_error(ECREATE));
	}
	table->start_time = get_timestamp();
	if (table->start_time == -1)
		return (assert_error(EGETTIME));
	i = -1;
	while (table->philos[++i].id)
	{
		if (pthread_join(table->philos[i].philo, NULL) != SUCCES)
			return (assert_error(EJOIN));
	}
}
