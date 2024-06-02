/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:04:12 by aaitelka          #+#    #+#             */
/*   Updated: 2024/06/02 02:27:21 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

void	*routine()
{
	write (1, "feel like a philo\n", 18);
}

void	create_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != SUCCES)
		write(STDERR_FILENO, ERR_MUTEX_INIT, strlen(ERR_MUTEX_INIT));
}

void	create_threads(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&philo->philos[i], NULL, routine, NULL) != SUCCES)
			write(STDERR_FILENO, ERR_THREAD_CREATE, strlen(ERR_THREAD_CREATE));
		i++;
	}
}

void	join_treads(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(philo->philos[i], NULL) != SUCCES)
			write(STDERR_FILENO, ERR_THREAD_JOIN, strlen(ERR_THREAD_JOIN));
		i++;
	}
}

void create_philos(t_philo *philo)
{
	int			i;
	int			count;

	i = 0;
	count = philo->count;
	philo->philos = malloc(count);
	if (!philo->philos)
		write(STDERR_FILENO, ERR_ALLOCATION, strlen(ERR_ALLOCATION));
	philo->forks = malloc(count);
	if (!philo->forks)
		write(STDERR_FILENO, ERR_ALLOCATION, strlen(ERR_ALLOCATION));
	create_threads(philo, count);
	join_treads(philo, count);
	
}

void	init_philos(t_philo *philo, int ac, char **av)
{
	int		i;
	long	size;

	i = -1;
	size = (ac - 2);
	philo->count = atol(av[1]);
	if (ac == 5)
		philo->time_to[MUST_EAT] = i;
	while (++i < size)
		philo->time_to[i] = atol(av[i + 2]);
}

void	launch(t_philo *philo, int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
	{
		init_philos(philo, ac ,av);
		create_philos(philo);
	}
	else
		printf("Error args\n");
}

int	main(int ac, char **av)
{
	t_philo	philo;

	launch(&philo, ac, av);
	return (EXIT_SUCCESS);
}
