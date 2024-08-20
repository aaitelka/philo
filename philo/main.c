/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:00:51 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/20 16:08:41 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	simulate(t_table *table, char **av)
{
	observer(table->philos);
	create_table(table, av);
}

void	release_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&table->philos[i].fork);
	pthread_mutex_destroy(&table->lock);
	free(table->philos);
}

void leak()
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_table table;
	int		exit_code;
	// atexit(leak);
	exit_code = 0;
	if ((argc < 5 || argc > 6) && ++exit_code)
		return (exit_code);
	else
		simulate(&table, argv);
	release_table(&table);
	return (SUCCES);
}
