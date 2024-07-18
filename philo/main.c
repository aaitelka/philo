/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:04:12 by aaitelka          #+#    #+#             */
/*   Updated: 2024/07/18 15:20:48 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

// EAT
// SLEEP
// THINK
// DIE

long	get_timestamp()
{
	struct timeval	tv;
	long			timestamp;

	if (gettimeofday(&tv, NULL) == -1)
			write(1, EGETTIME, strlen(EGETTIME));
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timestamp);
}

void	delay(long millis)
{
	struct timeval	tv;
	long			timestamp;

	sleep(50);
	if (gettimeofday(&tv, NULL) == -1)
		write(1, EGETTIME, strlen(EGETTIME));
	timestamp = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	long mil = get_timestamp();
	while (1)
	{
		if (mil >= millis)
			break ;
		usleep(20);
	}
}

void ft_lock(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->forks[id]);
	philo->forks_count = 0;
	philo->id++;
	pthread_mutex_unlock(&philo->forks[id]);
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->id]);
	if (philo->id % 2)
		pthread_mutex_lock(&philo->forks[philo->id + 1]);
	else
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	printf("philo %d has taken a fork\n", philo->id);
}

void take_own_fork(t_philo *philo)
{
	// if (philo->forks_count < 2)
	// 	philo->forks_count = 2;
	printf("philo %d has taken a fork\n", philo->id);
}

void	ft_eat(t_philo *philo, long time)
{
	printf("%ld %d is eating\n", time, philo->id);
	// sleep(philo->time_to[EAT]);
}

void	*routine(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	take_right_fork(philo);
	long ttime = get_timestamp() + philo->time_to[DIE];
	take_own_fork(philo);
	while (get_timestamp() <= ttime)
	{
		printf("time : %ld\n", ttime - get_timestamp());
		if (philo->id % 2)
			printf("%ld %d is eating\n", time, philo->id);
		else
			printf("%ld %d is sleeping\n", ttime, philo->id);
		// sleep(philo->time_to[EAT]);
		usleep(800);
	}
	pthread_mutex_unlock(&philo->forks[philo->id + 1]);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	return (NULL);
}

void	create_philos(t_philo *philo)
{
	int	i;

	i = 0;
	philo->id =0;
	philo->philos = malloc(philo->count * sizeof(pthread_t));
	if (!philo->philos)
		write(STDERR_FILENO, EALLOCATE, strlen(EALLOCATE));
	// set_philo_id(philo);
	while (i < philo->count)
	{
		ft_lock(philo, i);
		if (pthread_create(&philo->philos[i], NULL, routine, philo) != SUCCES) 
			write(STDERR_FILENO, ECREATE, strlen(ECREATE));
		// printf("thread [%d] created\n", i+1);
		i++;
	}
}

void	join_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->count)
	{
		if (pthread_detach(philo->philos[i]) != SUCCES)
			write(STDERR_FILENO, EJOIN, strlen(EJOIN));
		i++;
	}
}

void	create_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(philo->count * sizeof(pthread_mutex_t));
	if (!philo->forks)
		write(STDERR_FILENO, EALLOCATE, strlen(EALLOCATE));
	while (i < philo->count)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) != SUCCES)
			write(STDERR_FILENO, EMUTEXINIT, strlen(EMUTEXINIT));
		// printf("mutex [%d] created\n", i+1);
		i++;
	}
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
	init_philos(philo, ac ,av);
	create_mutex(philo);
	create_philos(philo);
	join_philos(philo);
}

int input_error(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void parse(char **av)
{
	int	result;

	if (input_error(av))
		printf("Error input\n");

}

void	destroy_threads(t_philo *philo)
{
	int i;

	i = 0;
	while (&philo->forks[i])
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	philo;
	
	if (ac == 5 || ac == 6)
	{
		// parse(av);
		launch(&philo, ac, av);
	}
	else
		printf("Error args\n");
	// destroy_threads(&philo);
	return (EXIT_SUCCESS);
}
