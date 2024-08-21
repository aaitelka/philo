/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:00:51 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/21 15:41:27 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_release(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_mutex_destroy(&table->philos[i].fork) != SUCCESS)
			return (ft_error(MEMUTEXDESTROY));
	}
	if (pthread_mutex_destroy(&table->lock) != SUCCESS)
		return (ft_error(MEMUTEXDESTROY));
	free(table->philos);
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc < 5 || argc > 6)
		return (FAILURE);
	else
		ft_simulate(&table, argv);
	ft_release(&table);
	return (SUCCESS);
}
