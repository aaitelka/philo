/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:00:26 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/31 15:59:46 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_release(t_table *table)
{
	int	index;

	index = -1;
	while (table->is_done && ++index < SEM_SIZE)
	{
		if (table->sem[index])
			sem_close(table->sem[index]);
	}
	free(table->philos);
	table->philos = NULL;
}

static void	ft_killall(t_table *table)
{
	int	index;

	index = -1;
	while (++index < table->philo_count)
	{
		if (table->philos[index].philo > 0)
			kill(table->philos[index].philo, SIGKILL);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	if (argc == 5 || argc == 6)
	{
		ft_simulate(&table, argv);
		ft_killall(&table);
		ft_release(&table);
	}
	else
		return (ft_error(MEARGS), FAILURE);
	return (SUCCESS);
}
