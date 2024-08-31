/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:00:38 by aaitelka          #+#    #+#             */
/*   Updated: 2024/08/31 02:27:18 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_locks(t_table *table)
{
	int		i;
	char	*sem[SEM_SIZE];

	i = -1;
	sem[LOCK] = NLOCK;
	sem[TIME] = NTIME;
	sem[PRINT] = NPRINT;
	sem[ACCESS] = NACCESS;
	table->name = sem;
	while (++i < SEM_SIZE)
	{
		sem_unlink(sem[i]);
		if (i == 0)
			table->sem[i] = sem_open(sem[i], O_CREAT, 0644, table->philo_count);
		else
			table->sem[i] = sem_open(sem[i], O_CREAT, 0644, 1);
		if (table->sem[i] == SEM_FAILED)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	ft_philos(t_table *table, t_philo *philo)
{
	int	index;

	index = 0;
	sem_wait(table->sem[TIME]);
	table->start_time = ft_gettimestamp();
	sem_post(table->sem[TIME]);
	while (index < table->philo_count)
	{
		philo[index].table = table;
		philo[index].philo = fork();
		if (table->philos[index].philo == 0)
		{
			pthread_create(&philo->observer, NULL, ft_observer, philo);
			pthread_detach(philo->observer);
			ft_routine(&table->philos[index]);
			exit(EXIT_SUCCESS);
		}
		else if (table->philos[index].philo == ERROR)
			return (EFORK);
		index++;
	}
	return (SUCCESS);
}

static void	ft_wait(t_table *table)
{
	pid_t	result;
	int		status;

	while (table->is_done == false)
	{
		result = waitpid(-1, &status, WNOHANG);
		if (result > 0)
		{
			if (WIFEXITED(status) || WIFSIGNALED(status))
			{
				table->is_done = true;
				break ;
			}
		}
	}
}

static void	ft_table(t_table *table, char **argv)
{
	int	index;

	index = -1;
	while (++index < 3)
		table->timeto[index] = ft_tolong(argv[index + 2]);
	if (argv[5])
	{
		table->timeto[MUST_EAT] = ft_tolong(argv[5]);
		table->has_must_eat = true;
	}
	else
		table->timeto[MUST_EAT] = -1;
	index = -1;
	while (++index < table->philo_count)
		table->philos[index].id = index + 1;
	table->is_done = false;
}

void	ft_simulate(t_table *table, char **argv)
{
	table->philo_count = ft_tolong(argv[1]);
	if (table->philo_count == -1)
		return (ft_error(MEARGS));
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		return (ft_error(MEALLOCATE));
	ft_table(table, argv);
	if (ft_check_args(table))
		return (ft_error(MEARGS));
	if (ft_locks(table) != SUCCESS)
		return (ft_error(MEMUTEXINIT));
	if (ft_philos(table, table->philos) != SUCCESS)
		return (ft_error(MEFORK));
	ft_wait(table);
}
