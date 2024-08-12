/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:04:12 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/12 20:12:34 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{	
	int index;
	t_table	*table;
	t_philo	*philos;
	
	table = (t_table *)arg;
	philos = table->philos;
	long time = table->timeto[EAT] + get_timestamp();

	return (NULL);
}

void realease(struct s_table *table)
{
	if (table->philos)
	{
		pthread_mutex_destroy(&table->philos->fork);
		free(table->philos);
	}
}

void simulate(struct s_table *table, char **av)
{
	create_table(table, av);
	// realease(table);
}


void print_table(struct s_table *table)
{
	printf("----------------------------------------\n");
	printf("philo_count = %d\n", table->philo_count);
	printf("start_time = %ld\n", table->start_time);
	printf("timeto[DIE] = %ld\n", table->timeto[DIE]);
	printf("timeto[EAT] = %ld\n", table->timeto[EAT]);
	printf("timeto[SLEEP] = %ld\n", table->timeto[SLEEP]);
	printf("timeto[MUST_EAT] = %ld\n", table->timeto[MUST_EAT]);
	printf("philos = %p\n", table->philos);
	printf("----------------------------------------\n");
}

int	main(int ac, char **av)
{
	t_table	table;
	int		exit_status;

	exit_status = 0;
	if ((ac < 5 || ac > 6) && ++exit_status)
		ft_logger(EARGS);
	else
		simulate(&table, av);
	// print_table(&table);
	return (exit_status);
}
