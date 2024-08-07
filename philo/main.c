/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:04:12 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/07 14:07:06 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo id = %d & address = %p\n", philo->id, philo->philo);
	return (NULL);
}

void realease(struct s_table *table)
{
	pthread_mutex_destroy(&table->philos->fork);
	free(table->philos);
}

void simulate(struct s_table *table, char **av)
{
	create(table, av, routine);
	realease(table);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		exit_status;

	exit_status = 0;
	if ((ac < 5 || ac > 6) && --exit_status)
		printf("%s", "Error: wrong argument\n");
	else
		simulate(&table, av);
	return (exit_status);
}
