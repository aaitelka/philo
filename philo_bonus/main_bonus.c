/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:00:26 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/28 19:01:18 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


static void	ft_release(t_table *table)
{
	int	i;

	i = -1;
	while (++i < SEM_SIZE)
		sem_close(table->sem[i]);
	while (table->philo_count--)
		kill(table->philos[table->philo_count].philo, SIGKILL);

	free(table->philos);		
}

void	*main_observer(void *arg)
{
	while (true)
	{
		if (ft_is_done((t_table *)arg))
			printf("DONE\n");
	}
}

// void leak()
// {
// 	system("leaks philo_bonus");
// }

int	main(int argc, char **argv)
{
	t_table	table;

	memset(&table, 0, sizeof(t_table));
	// atexit(leak);
	pthread_t observer;
	pthread_create(&observer, NULL, main_observer, &table);
	if (argc == 5 || argc == 6)
	{
		ft_simulate(&table, argv);
		if (table.is_done)
			ft_release(&table);
	}
	else
		return (ft_error(MEARGS), FAILURE);
	return (SUCCESS);
}
